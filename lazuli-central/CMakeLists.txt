cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lazuli-dentral)

target_sources(app PRIVATE src/main.c)

set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)

target_link_libraries(app PRIVATE zephyr_interface zephyr)
zephyr_linker_sources(SECTIONS sections-rom.ld)

foreach(web_resource
  index.html
    )
  generate_inc_file_for_target(
    app
    src/web_resources/${web_resource}
    ${gen_dir}/${web_resource}.gz.inc
    --gzip
  )
endforeach()