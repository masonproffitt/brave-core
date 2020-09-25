/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/permission_rules/user_activity_frequency_cap.h"

#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/internal/frequency_capping/frequency_capping_util.h"
#include "bat/ads/internal/platform/platform_helper.h"
#include "bat/ads/internal/time_util.h"

namespace ads {

UserActivityFrequencyCap::UserActivityFrequencyCap(
    const AdsImpl* const ads)
    : ads_(ads) {
  DCHECK(ads_);
}

UserActivityFrequencyCap::~UserActivityFrequencyCap() = default;

bool UserActivityFrequencyCap::IsAllowed() {
  const UserActivityHistoryMap history =
      ads_->get_user_activity()->get_history();
  if (!DoesRespectCap(history)) {
    return false;
  }

  return true;
}

std::string UserActivityFrequencyCap::get_last_message() const {
  return last_message_;
}

bool UserActivityFrequencyCap::DoesRespectCap(
    const UserActivityHistoryMap& history) {
  if (PlatformHelper::GetInstance()->IsMobile()) {
    return true;
  }

  const uint64_t time_constraint = base::Time::kSecondsPerHour;

  const uint64_t cap = 1;

  int count = 0;

  for (const auto& entry : history) {
    const UserActivityHistory user_activity_history = entry.second;

    if (OccurrencesForRollingTimeConstraint(user_activity_history,
        time_constraint, cap) > 0) {
      count++;
    }
  }

  if (count < 2) {
    return false;
  }

  return true;
}

}  // namespace ads
