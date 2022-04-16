#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh

cp -r ${THIRD_PARTY_PATH}/localization_msf ${NARUTO_APOLLO_ROOT}/bin/library





