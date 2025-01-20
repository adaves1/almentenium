

#include "src/android_webview/browser/component_updater/masked_domain_list_component_loader.h"

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "src/android_webview/browser/aw_app_defined_websites.h"
#include "src/android_webview/common/aw_features.h"
#include "src/base/feature_list.h"
#include "src/base/functional/bind.h"
#include "src/base/logging.h"
#include "src/base/task/thread_pool.h"
#include "src/components/component_updater/android/loader_policies/masked_domain_list_component_loader_policy.h"
#include "src/content/public/browser/network_service_instance.h"
#include "src/mojo/public/cpp/base/proto_wrapper.h"
#include "src/services/network/public/cpp/features.h"
#include "src/services/network/public/mojom/network_service.mojom.h"

namespace {
void UpdateMaskedDomainList(mojo_base::ProtoWrapper mdl,
                            const std::vector<std::string>& exclusion_list) {
  content::GetNetworkService()->UpdateMaskedDomainList(std::move(mdl),
                                                       exclusion_list);
}
}  // namespace

namespace android_webview {

// Add MaskedDomainListComponentLoaderPolicy to the given policies vector, if
// the component is enabled.
void LoadMaskedDomainListComponent(ComponentLoaderPolicyVector& policies) {
  if (!base::FeatureList::IsEnabled(network::features::kMaskedDomainList)) {
    return;
  }

  DVLOG(1) << "Registering Masked Domain List component for loading in "
              "embedded WebView.";

  policies.push_back(std::make_unique<
                     component_updater::MaskedDomainListComponentLoaderPolicy>(
      /* on_list_ready=*/base::BindRepeating(
          [](base::Version version,
             std::optional<mojo_base::ProtoWrapper> mdl) {
            auto exclusion_policy = static_cast<AppDefinedDomainCriteria>(
                features::kWebViewIpProtectionExclusionCriteria.Get());

            if (mdl.has_value()) {
              AppDefinedWebsites::GetInstance()->GetAppDefinedDomains(
                  std::move(exclusion_policy),
                  base::BindOnce(&UpdateMaskedDomainList,
                                 std::move(mdl.value())));
            } else {
              LOG(ERROR) << "Could not read Masked Domain List file";
            }
          })));
}

}  // namespace android_webview
