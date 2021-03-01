# SPDX-FileCopyrightText: Huawei Inc.
#
# SPDX-License-Identifier: Apache-2.0

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

do_install_append_qemuall() {
        install -D -m0644 ${WORKDIR}/wired.network ${D}${systemd_unitdir}/network/80-wired.network
}
