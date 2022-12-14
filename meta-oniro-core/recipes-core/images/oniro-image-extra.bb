# SPDX-FileCopyrightText: Huawei Inc.
#
# SPDX-License-Identifier: MIT

require recipes-graphics/images/core-image-weston.bb
require oniro-image-common.inc

SUMMARY = "Oniro Project Wayland image including the base OS \
software stack"

# The weston image pulls in package manager. We have a root filesystem that is
# defaulted to read-only so a package manager would make little sense using
# such a image feature.
IMAGE_FEATURES:remove = "package-management"

# Needed to start weston
SYSTEMD_DEFAULT_TARGET = "graphical.target"
