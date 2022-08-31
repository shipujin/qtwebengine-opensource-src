// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "services/service_manager/switches.h"

namespace service_manager {
namespace switches {

// Enable the tracing service.
const char kEnableTracing[] = "enable-service-manager-tracing";

#if defined(TOOLKIT_QT)
// Pass on parent application name
const char kApplicationName[] = "application-name";
// Preload widevinepaths for sandbox
const char kCdmWidevinePath[] = "widevine-path";
#endif

}  // namespace switches
}  // namespace service_manager