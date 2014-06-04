/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.bootloader", bootloader);

    if (strstr(bootloader, "G900W8")) {
        /* kltecan */
        gsm_properties();
        property_set("ro.build.fingerprint", "samsung/kltecan/klte:4.4.2/KOT49H/G900W8VLUBMJ4:user/release-keys");
        property_set("ro.build.description", "kltecan-user 4.4.2 KOT49H G900W8VLUBMJ4 release-keys");
        property_set("ro.product.model", "SM-G900W8");
        property_set("ro.product.device", "kltecan");
    } else if (strstr(bootloader, "G900P")) {
        /* kltespr */
        cdma_properties("1");
        property_set("ro.build.fingerprint", "samsung/kltespr/klte:4.4.2/KOT49H/G900PVPUBMJ4:user/release-keys");
        property_set("ro.build.description", "kltespr-user 4.4.2 KOT49H G900PVPUBMJ4 release-keys");
        property_set("ro.product.model", "SM-G900P");
        property_set("ro.product.device", "kltespr");
    } else if (strstr(bootloader, "G900T")) {
        /* kltetmo */
        gsm_properties();
        property_set("ro.build.fingerprint", "samsung/kltetmo/klte:4.4.2/KOT49H/G900TUVUBMI7:user/release-keys");
        property_set("ro.build.description", "kltetmo-user 4.4.2 KOT49H G900TUVUBMI7 release-keys");
        property_set("ro.product.model", "SM-G900T");
        property_set("ro.product.device", "kltetmo");
    } else if (strstr(bootloader, "G900V")) {
        /* kltevzw */
        cdma_properties("1");
        property_set("ro.build.fingerprint", "Verizon/kltevzw/klte:4.4.2/KOT49H/G900VOYUBMJ3:user/release-keys");
        property_set("ro.build.description", "kltevzw-user 4.4.2 KOT49H G900VOYUBMJ3 release-keys");
        property_set("ro.product.model", "SM-G900V");
        property_set("ro.product.device", "kltevzw");
        property_set("ro.telephony.default_cdma_sub", "0");
        property_set("ro.cdma.home.operator.alpha", "Verizon");
        property_set("ro.cdma.home.operator.numeric", "311480");
    } else if (strstr(bootloader, "G900F")) {
        /* kltexx */
        gsm_properties();
        property_set("ro.build.fingerprint", "samsung/kltexx/klte:4.4.2/KOT49H/G900FXXU1ANCE:user/release-keys");
        property_set("ro.build.description", "kltexx-user 4.4.2 KOT49H G900FXXU1ANCE release-keys");
        property_set("ro.product.model", "SM-G900F");
        property_set("ro.product.device", "kltexx");
    }
    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}

void gsm_properties()
{
    property_set("telephony.lteOnGsmDevice", "1");
    property_set("ro.telephony.default_network", "9");
}

void cdma_properties(char cdma_sub[])
{
    property_set("ro.telephony.default_cdma_sub", cdma_sub); // 0: RUIM/SIM  1: NV
    property_set("ro.gps.set_privacy", "1");
    property_set("ro.telephony.ril.v3", "newDriverCallU");
    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ro.telephony.default_network", "10");
}
