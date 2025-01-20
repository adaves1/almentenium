// Copyright 2025 Anthony Daves

#include "src/android_webview/browser/component_updater/loader_policies/origin_trials_component_loader_policy.h"

#include <stdint.h>
#include <stdio.h>

#include <string>
#include <utility>
#include <vector>

#include "src/android_webview/browser/aw_browser_process.h"
#include "src/base/containers/flat_map.h"
#include "src/base/files/scoped_file.h"
#include "src/base/values.h"
#include "src/base/version.h"
#include "src/components/component_updater/android/component_loader_policy.h"
#include "src/components/component_updater/installer_policies/origin_trials_component_installer.h"
#include "src/components/embedder_support/origin_trials/component_updater_utils.h"

namespace android_webview {

namespace {

// Persisted to logs, should never change.
constexpr char kOriginTrialsComponentMetricsSuffix[] = "OriginTrials";

}  // namespace

OriginTrialsComponentLoaderPolicy::OriginTrialsComponentLoaderPolicy() =
    default;

OriginTrialsComponentLoaderPolicy::~OriginTrialsComponentLoaderPolicy() =
    default;

void OriginTrialsComponentLoaderPolicy::ComponentLoaded(
    const base::Version& version,
    base::flat_map<std::string, base::ScopedFD>& fd_map,
    base::Value::Dict manifest) {
  // Read the configuration from the manifest and set values in browser
  // local_state. These will be used on the next browser restart.
  // If an individual configuration value is missing, treat as a reset to the
  // browser defaults.
  embedder_support::ReadOriginTrialsConfigAndPopulateLocalState(
      android_webview::AwBrowserProcess::GetInstance()->local_state(),
      std::move(manifest));
}

void OriginTrialsComponentLoaderPolicy::ComponentLoadFailed(
    component_updater::ComponentLoadResult /*error*/) {}

void OriginTrialsComponentLoaderPolicy::GetHash(
    std::vector<uint8_t>* hash) const {
  component_updater::OriginTrialsComponentInstallerPolicy::GetComponentHash(
      hash);
}

std::string OriginTrialsComponentLoaderPolicy::GetMetricsSuffix() const {
  return kOriginTrialsComponentMetricsSuffix;
}

}  // namespace android_webview
