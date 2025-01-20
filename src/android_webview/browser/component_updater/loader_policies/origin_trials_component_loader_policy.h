// Copyright 2025 Anthony Daves

#ifndef ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_LOADER_POLICIES_ORIGIN_TRIALS_COMPONENT_LOADER_POLICY_H_
#define ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_LOADER_POLICIES_ORIGIN_TRIALS_COMPONENT_LOADER_POLICY_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "src/base/containers/flat_map.h"
#include "src/base/files/scoped_file.h"
#include "src/base/values.h"
#include "src/components/component_updater/android/component_loader_policy.h"

namespace base {
class Version;
}  // namespace base

namespace android_webview {

// OriginTrialsComponentLoaderPolicy defines a loader responsible
// for receiving origin trials config.
class OriginTrialsComponentLoaderPolicy
    : public component_updater::ComponentLoaderPolicy {
 public:
  OriginTrialsComponentLoaderPolicy();
  ~OriginTrialsComponentLoaderPolicy() override;

  OriginTrialsComponentLoaderPolicy(const OriginTrialsComponentLoaderPolicy&) =
      delete;
  OriginTrialsComponentLoaderPolicy& operator=(
      const OriginTrialsComponentLoaderPolicy&) = delete;

 private:
  // The following methods override ComponentLoaderPolicy.
  void ComponentLoaded(const base::Version& version,
                       base::flat_map<std::string, base::ScopedFD>& fd_map,
                       base::Value::Dict manifest) override;
  void ComponentLoadFailed(
      component_updater::ComponentLoadResult error) override;
  void GetHash(std::vector<uint8_t>* hash) const override;
  std::string GetMetricsSuffix() const override;
};

}  // namespace android_webview

#endif  // ANDROID_WEBVIEW_BROWSER_COMPONENT_UPDATER_LOADER_POLICIES_ORIGIN_TRIALS_COMPONENT_LOADER_POLICY_H_
