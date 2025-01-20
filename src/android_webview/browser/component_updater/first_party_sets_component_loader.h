

#ifndef ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_FIRST_PARTY_SETS_COMPONENT_LOADER_H_
#define ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_FIRST_PARTY_SETS_COMPONENT_LOADER_H_

#include <memory>
#include <vector>

namespace component_updater {
class ComponentLoaderPolicy;
}  // namespace component_updater

namespace android_webview {

using ComponentLoaderPolicyVector =
    std::vector<std::unique_ptr<component_updater::ComponentLoaderPolicy>>;

void LoadFpsComponent(ComponentLoaderPolicyVector& policies);

}  // namespace android_webview

#endif  // ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_FIRST_PARTY_SETS_COMPONENT_LOADER_H_
