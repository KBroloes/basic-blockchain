cmake_minimum_required(VERSION 3.8)
project(basic_blockchain)
include_directories(/usr/local/opt/openssl/include/)
find_library(CRYPTO_LIB crypto)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        base58.h
        common.h
        ec.h
        endian.h
        hash.h
        main.c
        tx.h
        varint.h)

add_executable(basic_blockchain ${SOURCE_FILES})

target_link_libraries(basic_blockchain "${CRYPTO_LIB}")
