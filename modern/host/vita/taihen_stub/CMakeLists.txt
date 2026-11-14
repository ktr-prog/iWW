# Generates the user-mode taiHEN import stub (libtaihen_stub.a) that SceShaccCgExt links against, using the
# toolchain's own vita_create_stubs() on taiHEN's exports.yml - the same call taiHEN's own build uses. The core
# vdpm-bootstrapped toolchain doesn't ship this stub, so the Vita CI builds it here and copies it into the prefix.
# TAIHEN_YML is passed in by CI (the path to a checkout of taiHEN's exports.yml).
cmake_minimum_required(VERSION 3.10)
project(taihen_stub C)
include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)
vita_create_stubs(taihen-stubs taihen "${TAIHEN_YML}")
add_custom_target(stubs ALL DEPENDS taihen_stub taihen_stub_weak)
