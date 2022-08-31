// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'chrome://resources/cr_elements/cr_icon_button/cr_icon_button.m.js';
import 'chrome://resources/cr_elements/cr_button/cr_button.m.js';
import 'chrome://resources/cr_elements/cr_input/cr_input.m.js';
import 'chrome://resources/cr_elements/cr_checkbox/cr_checkbox.m.js';
import 'chrome://resources/cr_elements/shared_vars_css.m.js';
import 'chrome://resources/cr_components/customize_themes/customize_themes.js';
import 'chrome://resources/cr_components/customize_themes/customize_themes.mojom-lite.js';
import './shared_css.js';
import '../icons.js';

import {loadTimeData} from 'chrome://resources/js/load_time_data.m.js';
import {WebUIListenerBehavior} from 'chrome://resources/js/web_ui_listener_behavior.m.js';
import {html, Polymer} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import {AutogeneratedThemeColorInfo, ManageProfilesBrowserProxy, ManageProfilesBrowserProxyImpl, UserThemeChoice} from '../manage_profiles_browser_proxy.js';
import {navigateToPreviousRoute} from '../navigation_behavior.js';
import {isProfileCreationAllowed} from '../policy_helper.js';

Polymer({
  is: 'local-profile-customization',

  _template: html`{__html_template__}`,

  behaviors: [WebUIListenerBehavior],

  properties: {
    /**
     * The theme info used to display colored UI elements.
     * @type {!AutogeneratedThemeColorInfo}
     */
    profileThemeInfo: {
      type: Object,
      observer: 'onProfileThemeInfoChange_',
    },

    /**
     * The currently selected theme in the color picker.
     * @private {!customizeThemes.mojom.Theme}
     */
    selectedTheme_: {
      type: Object,
      observer: 'onSelectedThemeChange_',
    },

    /**
     * True if `selectedTheme_` doesn't need to be updated when
     * `profileThemeInfo` changes.
     * @private {boolean}
     */
    disableSelectedThemeUpdates_: {
      type: Boolean,
      value: false,
    },

    /**
     * The current profile name.
     * @private {string}
     */
    profileName_: {
      type: String,
      value: '',
    },

    /**
     * if true, a desktop shortcut will be created for the new profile.
     * @private {boolean}
     */
    createShortcut_: {
      type: Boolean,
      value: true,
    },

    /**
     * True if the profile shortcuts feature is enabled.
     * @private
     */
    isProfileShortcutsEnabled_: {
      type: Boolean,
      value: () => loadTimeData.getBoolean('profileShortcutsEnabled'),
    },

    /**
     * True if a profile is being created or imported.
     * @private {boolean}
     */
    createInProgress_: {
      type: Boolean,
      value: false,
    },

    /** @private */
    pattern_: {
      type: String,
      value: '.*\\S.*',
    },
  },

  /** @private {?ManageProfilesBrowserProxy} */
  manageProfilesBrowserProxy_: null,

  /** @override */
  created() {
    this.manageProfilesBrowserProxy_ =
        ManageProfilesBrowserProxyImpl.getInstance();
  },

  /** @override */
  ready() {
    this.sanityCheck_();
    this.addWebUIListener(
        'create-profile-finished', () => this.handleCreateProfileFinished_());
  },

  /**
   * @return {boolean}
   * @private
   */
  sanityCheck_() {
    if (!isProfileCreationAllowed()) {
      this.onClickBack_();
      return false;
    }
    return true;
  },

  /**
   * Determining whether 'Save' button is disabled.
   * @return {boolean}
   * @private
   */
  isSaveDisabled_() {
    return this.createInProgress_ || !this.profileName_ ||
        !this.$.nameInput.validate();
  },

  /**
   * Handler for the 'Save' button click event.
   * @param {!Event} event
   * @private
   */
  onSaveClick_(event) {
    if (!this.sanityCheck_()) {
      return;
    }

    if (this.createInProgress_) {
      return;
    }
    this.createInProgress_ = true;
    const createShortcut =
        this.isProfileShortcutsEnabled_ && this.createShortcut_;
    // TODO(crbug.com/1115056): Support avatar selection.
    this.manageProfilesBrowserProxy_.createProfile(
        this.profileName_, this.profileThemeInfo.color, '', true,
        createShortcut);
  },

  /** @private */
  onClickBack_() {
    navigateToPreviousRoute();
    this.reset_();
  },

  /** @private */
  reset_() {
    this.profileName_ = '';
    this.createShortcut_ = true;
    this.$.wrapper.scrollTop = 0;
  },

  /** @private */
  onProfileThemeInfoChange_() {
    if (this.disableSelectedThemeUpdates_) {
      return;
    }

    this.selectedTheme_ = {
      type: customizeThemes.mojom.ThemeType.kChrome,
      info: {
        chromeThemeId: this.profileThemeInfo.colorId,
      },
    };
  },

  /**
   * @return {!Promise}
   * @private
   */
  async onSelectedThemeChange_() {
    /** @type {UserThemeChoice} */
    let theme;
    if (this.selectedTheme_.type ===
        customizeThemes.mojom.ThemeType.kAutogenerated) {
      theme = {
        colorId: 0,
        color: this.selectedTheme_.info.autogeneratedThemeColors.frame.value
      };
    } else if (
        this.selectedTheme_.type === customizeThemes.mojom.ThemeType.kChrome) {
      theme = {
        colorId: /** @type {number} */ (this.selectedTheme_.info.chromeThemeId),
      };
    } else if (
        this.selectedTheme_.type === customizeThemes.mojom.ThemeType.kDefault) {
      theme = {
        colorId: -1,
      };
    }

    const newThemeInfo =
        await this.manageProfilesBrowserProxy_.getProfileThemeInfo(theme);
    this.disableSelectedThemeUpdates_ = true;
    this.profileThemeInfo = newThemeInfo;
    this.disableSelectedThemeUpdates_ = false;
  },

  /** @private */
  handleCreateProfileFinished_() {
    this.onClickBack_();
    this.createInProgress_ = false;
  }
});