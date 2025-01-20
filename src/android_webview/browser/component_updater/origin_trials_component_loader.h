

#ifndef ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_ORIGIN_TRIALS_COMPONENT_LOADER_H_
#define ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_ORIGIN_TRIALS_COMPONENT_LOADER_H_

#include "src/components/component_updater/android/component_loader_policy_forward.h"

namespace component_updater {
class ComponentLoaderPolicy;
}  // namespace component_updater

namespace android_webview {

// Adds origin trials ComponentLoaderPolicy to `policies`, if Origin Trials
// support is enabled.
void LoadOriginTrialsComponent(
    component_updater::ComponentLoaderPolicyVector& policies);

}  // namespace android_webview

#endif  // ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_ORIGIN_TRIALS_COMPONENT_LOADER_H_
