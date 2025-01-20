

#include "src/android_webview/browser/component_updater/first_party_sets_component_loader.h"

#include <memory>
#include <string>
#include <vector>

#include "src/android_webview/common/aw_switches.h"
#include "src/base/command_line.h"
#include "src/base/files/file.h"
#include "src/base/functional/bind.h"
#include "src/base/logging.h"
#include "src/base/version.h"
#include "src/components/component_updater/android/loader_policies/first_party_sets_component_loader_policy.h"
#include "src/content/public/browser/first_party_sets_handler.h"
#include "src/services/network/public/cpp/features.h"

namespace android_webview {

void LoadFpsComponent(ComponentLoaderPolicyVector& policies) {
  if (!base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kWebViewFpsComponent)) {
    return;
  }

  DVLOG(1) << "Registering first party sets component for loading in "
              "embedded WebView.";

  policies.push_back(
      std::make_unique<component_updater::FirstPartySetComponentLoaderPolicy>(
          base::BindRepeating([](base::Version version, base::File sets_file) {
            content::FirstPartySetsHandler::GetInstance()
                ->SetPublicFirstPartySets(version, std::move(sets_file));
          })));
}

}  // namespace android_webview
