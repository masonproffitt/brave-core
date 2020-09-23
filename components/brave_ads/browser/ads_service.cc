/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/browser/ads_service.h"

#include "components/pref_registry/pref_registry_syncable.h"
#include "bat/ads/pref_names.h"

namespace brave_ads {

AdsService::AdsService() = default;

AdsService::~AdsService() = default;

void AdsService::AddObserver(
    AdsServiceObserver* observer) {
  observers_.AddObserver(observer);
}

void AdsService::RemoveObserver(
    AdsServiceObserver* observer) {
  observers_.RemoveObserver(observer);
}

void AdsService::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterIntegerPref(
      ads::prefs::kVersion, ads::prefs::kCurrentVersionNumber);

  registry->RegisterIntegerPref(
      ads::prefs::kSupportedCountryCodesLastSchemaVersion, 0);

  registry->RegisterIntegerPref(
      ads::prefs::kSupportedCountryCodesSchemaVersion,
          ads::prefs::kSupportedCountryCodesSchemaVersionNumber);

  registry->RegisterBooleanPref(
      ads::prefs::kEnabled, false);

  registry->RegisterBooleanPref(
      ads::prefs::kShouldAllowAdConversionTracking, true);

  registry->RegisterUint64Pref(
      ads::prefs::kAdsPerHour, 2);
  registry->RegisterUint64Pref(
      ads::prefs::kAdsPerDay, 20);

  registry->RegisterBooleanPref(
      ads::prefs::kShouldAllowAdsSubdivisionTargeting, false);
  registry->RegisterStringPref(
      ads::prefs::kAdsSubdivisionTargetingCode, "AUTO");
  registry->RegisterStringPref(
      ads::prefs::kAutoDetectedAdsSubdivisionTargetingCode, "");

  registry->RegisterIntegerPref(
      ads::prefs::kIdleThreshold, 15);
  registry->RegisterBooleanPref(
      ads::prefs::kAdsWereDisabled, false);
  registry->RegisterBooleanPref(
      ads::prefs::kHasAdsP3AState, false);

  registry->RegisterBooleanPref(
      ads::prefs::kShouldShowMyFirstAdNotification, true);

  registry->RegisterBooleanPref(
      ads::prefs::kShouldShowOnboarding, true);
  registry->RegisterUint64Pref(
      ads::prefs::kOnboardingTimestamp, 0);
}

}  // namespace brave_ads
