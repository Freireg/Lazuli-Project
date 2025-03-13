#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#include <zephyr/fs/fs.h>
#include <zephyr/fs/littlefs.h>

static const char *now_str(void)
{
	static char buf[16]; /* ...HH:MM:SS.MMM */
	uint32_t now = k_uptime_get_32();
	unsigned int ms = now % MSEC_PER_SEC;
	unsigned int s;
	unsigned int min;
	unsigned int h;

	now /= MSEC_PER_SEC;
	s = now % 60U;
	now /= 60U;
	min = now % 60U;
	now /= 60U;
	h = now;

	snprintf(buf, sizeof(buf), "%u:%02u:%02u.%03u",
		 h, min, s, ms);
	return buf;
}

static int write_to_flash(char *fname, char* data, int len);

static int process_mpu6050(const struct device *dev)
{
	struct sensor_value temperature;
	struct sensor_value accel[3];
	struct sensor_value gyro[3];
  char log_data[255];
  int len;
	int rc = sensor_sample_fetch(dev);

	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ,
					accel);
	}
	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_GYRO_XYZ,
					gyro);
	}
	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_DIE_TEMP,
					&temperature);
	}
	if (rc == 0) {
		// printf("[%s]:%g Cel\n"
		//        "  accel %f %f %f m/s/s\n"
		//        "  gyro  %f %f %f rad/s\n",
		//        now_str(),
		//        sensor_value_to_double(&temperature),
		//        sensor_value_to_double(&accel[0]),
		//        sensor_value_to_double(&accel[1]),
		//        sensor_value_to_double(&accel[2]),
		//        sensor_value_to_double(&gyro[0]),
		//        sensor_value_to_double(&gyro[1]),
		//        sensor_value_to_double(&gyro[2]));
    len = snprintf(log_data, sizeof(log_data), "[%s]:%g Cel\n"
           "  accel %f %f %f m/s/s\n"
           "  gyro  %f %f %f rad/s\n",
           now_str(),
           sensor_value_to_double(&temperature),
           sensor_value_to_double(&accel[0]),
           sensor_value_to_double(&accel[1]),
           sensor_value_to_double(&accel[2]),
           sensor_value_to_double(&gyro[0]),
           sensor_value_to_double(&gyro[1]),
           sensor_value_to_double(&gyro[2]));
    write_to_flash("/lfs1/sensor_data.txt", log_data, len);
	} else {
		printf("sample fetch/get failed: %d\n", rc);
	}

	return rc;
}

static int lsdir(const char *path)
{
	int res;
	struct fs_dir_t dirp;
	static struct fs_dirent entry;

	fs_dir_t_init(&dirp);

	/* Verify fs_opendir() */
	res = fs_opendir(&dirp, path);
	if (res) {
		LOG_ERR("Error opening dir %s [%d]\n", path, res);
		return res;
	}

	LOG_PRINTK("\nListing dir %s ...\n", path);
	for (;;) {
		/* Verify fs_readdir() */
		res = fs_readdir(&dirp, &entry);

		/* entry.name[0] == 0 means end-of-dir */
		if (res || entry.name[0] == 0) {
			if (res < 0) {
				LOG_ERR("Error reading dir [%d]\n", res);
			}
			
		}

		if (entry.type == FS_DIR_ENTRY_DIR) {
			LOG_PRINTK("[DIR ] %s\n", entry.name);
		} else {
			LOG_PRINTK("[FILE] %s (size = %zu)\n",
				   entry.name, entry.size);
		}
	}

	/* Verify fs_closedir() */
	fs_closedir(&dirp);

	return res;
}

static int littlefs_flash_erase(unsigned int id)
{
	const struct flash_area *pfa;
	int rc;

	rc = flash_area_open(id, &pfa);
	if (rc < 0) {
		LOG_ERR("FAIL: unable to find flash area %u: %d\n",
			id, rc);
		return rc;
	}

	LOG_PRINTK("Area %u at 0x%x on %s for %u bytes\n",
		   id, (unsigned int)pfa->fa_off, pfa->fa_dev->name,
		   (unsigned int)pfa->fa_size);

	/* Optional wipe flash contents */
	if (IS_ENABLED(CONFIG_APP_WIPE_STORAGE)) {
		rc = flash_area_flatten(pfa, 0, pfa->fa_size);
		LOG_ERR("Erasing flash area ... %d", rc);
	}

	flash_area_close(pfa);
	return rc;
}
#define PARTITION_NODE DT_NODELABEL(lfs1)

#if DT_NODE_EXISTS(PARTITION_NODE)
FS_FSTAB_DECLARE_ENTRY(PARTITION_NODE);
#else /* PARTITION_NODE */
FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(storage);
static struct fs_mount_t lfs_storage_mnt = {
	.type = FS_LITTLEFS,
	.fs_data = &storage,
	.storage_dev = (void *)FIXED_PARTITION_ID(storage_partition),
	.mnt_point = "/lfs",
};
#endif /* PARTITION_NODE */

	struct fs_mount_t *mountpoint =
#if DT_NODE_EXISTS(PARTITION_NODE)
		&FS_FSTAB_ENTRY(PARTITION_NODE)
#else
		&lfs_storage_mnt
#endif
		;

static int littlefs_mount(struct fs_mount_t *mp)
{
	int rc;

	rc = littlefs_flash_erase((uintptr_t)mp->storage_dev);
	if (rc < 0) {
		return rc;
	}

	/* Do not mount if auto-mount has been enabled */
#if !DT_NODE_EXISTS(PARTITION_NODE) ||						\
	!(FSTAB_ENTRY_DT_MOUNT_FLAGS(PARTITION_NODE) & FS_MOUNT_FLAG_AUTOMOUNT)
	rc = fs_mount(mp);
	if (rc < 0) {
		LOG_PRINTK("FAIL: mount id %" PRIuPTR " at %s: %d\n",
		       (uintptr_t)mp->storage_dev, mp->mnt_point, rc);
		return rc;
	}
	LOG_PRINTK("%s mount: %d\n", mp->mnt_point, rc);
#else
	LOG_PRINTK("%s automounted\n", mp->mnt_point);
#endif

	return 0;
}

static int write_to_flash(char *fname, char* data, int len)
{
  struct fs_file_t file;
  int rc, ret;

  fs_file_t_init(&file);

  rc = fs_open(&file, fname, FS_O_CREATE | FS_O_RDWR | FS_O_APPEND);
  if (rc < 0) {
    LOG_ERR("FAIL: open %s: %d", fname, rc);
    return rc;
  }
  printf("File oppened\n");
  rc = fs_write(&file, data, len);
  if (rc < 0) {
    LOG_ERR("FAIL: write %s: %d", fname, rc);
  }
  printf("Data written\n");
  ret = fs_close(&file);
  if (ret < 0) {
    LOG_ERR("FAIL: close %s: %d", fname, ret);
    return ret;
  }
  printf("File closed\n");

  return (rc < 0 ? rc : 0);
}

int main(void)
{
  char fname1[255];
	char fname2[255];
	struct fs_statvfs sbuf;
  int rc = littlefs_mount(mountpoint);
  if (rc < 0) {
		return 0;
	}

	snprintf(fname1, sizeof(fname1), "%s/boot_count", mountpoint->mnt_point);
	snprintf(fname2, sizeof(fname2), "%s/pattern.bin", mountpoint->mnt_point);

	rc = fs_statvfs(mountpoint->mnt_point, &sbuf);
	if (rc < 0) {
		LOG_PRINTK("FAIL: statvfs: %d\n", rc);
		// goto out;
	}

	LOG_PRINTK("%s: bsize = %lu ; frsize = %lu ;"
		   " blocks = %lu ; bfree = %lu\n",
		   mountpoint->mnt_point,
		   sbuf.f_bsize, sbuf.f_frsize,
		   sbuf.f_blocks, sbuf.f_bfree);

	// rc = lsdir(mountpoint->mnt_point);
	// if (rc < 0) {
	// 	LOG_PRINTK("FAIL: lsdir %s: %d\n", mountpoint->mnt_point, rc);
	// 	goto out;
	// }

	// rc = littlefs_binary_file_adj(fname2);
	// if (rc) {
	// 	goto out;
	// }

	// rc = fs_unmount(mountpoint); 

  const struct device *const mpu6050 = DEVICE_DT_GET_ONE(invensense_mpu6050);

	if (!device_is_ready(mpu6050)) {
		printf("Device %s is not ready\n", mpu6050->name);
		return 0;
	}
  printf("\nDevice %s is ready\n", mpu6050->name);

  // for(int i = 0; i < 2; i++)
  // {
  //   rc = process_mpu6050(mpu6050);
  //   printf("Reading sample %d\n", i);
  //   if(rc != 0)
  //   {
  //     printf("Error reading sensor data\n");
  //     break;
  //   }   
  //   k_sleep(K_MSEC(2000));
  // }
  
	return 0;
}
