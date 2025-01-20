

#include "src/android_webview/browser/component_updater/origin_trials_component_loader.h"

#include <memory>

#include "src/android_webview/browser/component_updater/loader_policies/origin_trials_component_loader_policy.h"
#include "src/components/component_updater/android/component_loader_policy.h"
#include "src/components/component_updater/android/component_loader_policy_forward.h"

namespace android_webview {

void LoadOriginTrialsComponent(
    component_updater::ComponentLoaderPolicyVector& policies) {
  policies.push_back(std::make_unique<OriginTrialsComponentLoaderPolicy>());
}

}  // namespace android_webview
