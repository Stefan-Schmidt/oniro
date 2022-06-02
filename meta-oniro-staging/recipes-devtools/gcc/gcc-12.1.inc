require gcc-common.inc

# Third digit in PV should be incremented after a minor release

PV = "12.1.0"

# BINV should be incremented to a revision after a minor gcc release

BINV = "12.1.0"

MAJOR = "12"
# SNAPSHOT = "20220313"

FILESEXTRAPATHS =. "${FILE_DIRNAME}/gcc:${FILE_DIRNAME}/gcc/backport:"

DEPENDS =+ "mpfr gmp libmpc zlib flex-native"
NATIVEDEPS = "mpfr-native gmp-native libmpc-native zlib-native flex-native"

LICENSE = "GPL-3.0-with-GCC-exception & GPL-3.0-only"

LIC_FILES_CHKSUM = "\
    file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552 \
    file://COPYING3;md5=d32239bcb673463ab874e80d47fae504 \
    file://COPYING3.LIB;md5=6a6a8e020838b23406c81b19c1d46df6 \
    file://COPYING.LIB;md5=2d5025d4aa3495befef8f17206a5b0a1 \
    file://COPYING.RUNTIME;md5=fe60d87048567d4fe8c8a0ed2448bcc8 \
"

RELEASE ?= "1ea978e3066ac565a1ec28a96a4d61eaf38e2726"
BASEURI ?= "https://github.com/gcc-mirror/gcc/archive/${RELEASE}.tar.gz;downloadfilename=gcc-${PV}-${RELEASE}.tar.gz"

# For snapshots
#BASEURI ?= "https://mirror.koddos.net/gcc/snapshots/${MAJOR}-${SNAPSHOT}/gcc-${MAJOR}-${SNAPSHOT}.tar.xz"
SRC_URI = "\
           ${BASEURI} \
           file://0001-gcc-4.3.1-ARCH_FLAGS_FOR_TARGET.patch \
           file://0002-gcc-poison-system-directories.patch \
           file://0004-64-bit-multilib-hack.patch \
           file://0007-Use-the-defaults.h-in-B-instead-of-S-and-t-oe-in-B.patch \
           file://0009-cpp-honor-sysroot.patch \
           file://0011-Define-GLIBC_DYNAMIC_LINKER-and-UCLIBC_DYNAMIC_LINKE.patch \
           file://0014-libtool.patch \
           file://0015-gcc-armv4-pass-fix-v4bx-to-linker-to-support-EABI.patch \
           file://0016-Use-the-multilib-config-files-from-B-instead-of-usin.patch \
           file://0017-Avoid-using-libdir-from-.la-which-usually-points-to-.patch \
           file://0019-Ensure-target-gcc-headers-can-be-included.patch \
           file://0020-Don-t-search-host-directory-during-relink-if-inst_pr.patch \
           file://0023-libcc1-fix-libcc1-s-install-path-and-rpath.patch \
           file://0024-handle-sysroot-support-for-nativesdk-gcc.patch \
           file://0025-Search-target-sysroot-gcc-version-specific-dirs-with.patch \
           file://0028-Add-ssp_nonshared-to-link-commandline-for-musl-targe.patch \
           file://0033-Re-introduce-spe-commandline-options.patch \
           file://0034-libgcc_s-Use-alias-for-__cpu_indicator_init-instead-.patch \
           file://0035-gentypes-genmodes-Do-not-use-__LINE__-for-maintainin.patch \
           file://0036-mingw32-Enable-operation_not_supported.patch \
           file://0037-libatomic-Do-not-enforce-march-on-aarch64.patch \
           file://0006-If-CXXFLAGS-contains-something-unsupported-by-the-bu.patch \
           file://0001-Fix-install-path-of-linux64.h.patch \
"
SRC_URI[sha256sum] = "37f4815d27485cd84bfd725598a5afe53714ce4ecdfdef4bc266c086ae165367"

S = "${TMPDIR}/work-shared/gcc-${PV}-${PR}/gcc-${RELEASE}"

# For dev release snapshotting
#S = "${TMPDIR}/work-shared/gcc-${PV}-${PR}/gcc-${MAJOR}-${SNAPSHOT}"
#B = "${WORKDIR}/gcc-${PV}/build.${HOST_SYS}.${TARGET_SYS}"

# Language Overrides
FORTRAN = ""
JAVA = ""

SSP ?= "--disable-libssp"
SSP:mingw32 = "--enable-libssp"

EXTRA_OECONF_BASE = "\
    ${SSP} \
    --enable-libitm \
    --enable-lto \
    --disable-bootstrap \
    --with-system-zlib \
    ${@'--with-linker-hash-style=${LINKER_HASH_STYLE}' if '${LINKER_HASH_STYLE}' else ''} \
    --enable-linker-build-id \
    --with-ppl=no \
    --with-cloog=no \
    --enable-checking=release \
    --enable-cheaders=c_global \
    --without-isl \
"

EXTRA_OECONF_INITIAL = "\
    --disable-libgomp \
    --disable-libitm \
    --disable-libquadmath \
    --with-system-zlib \
    --disable-lto \
    --disable-plugin \
    --enable-linker-build-id \
    --enable-decimal-float=no \
    --without-isl \
    --disable-libssp \
"

EXTRA_OECONF_PATHS = "\
    --with-gxx-include-dir=/not/exist{target_includedir}/c++/${BINV} \
    --with-sysroot=/not/exist \
    --with-build-sysroot=${STAGING_DIR_TARGET} \
"

# Is a binutils 2.26 issue, not gcc
CVE_CHECK_IGNORE += "CVE-2021-37322"