// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file was generated by:
//   tools/json_schema_compiler/compiler.py.
// NOTE: The format of types has changed. 'FooType' is now
//   'chrome.passwordsPrivate.FooType'.
// Please run the closure compiler before committing changes.
// See
// https://chromium.googlesource.com/chromium/src/+/master/docs/closure_compilation.md

/** @fileoverview Externs generated from namespace: passwordsPrivate */

/** @const */
chrome.passwordsPrivate = {};

/**
 * @enum {string}
 */
chrome.passwordsPrivate.PlaintextReason = {
  VIEW: 'VIEW',
  COPY: 'COPY',
  EDIT: 'EDIT',
};

/**
 * @enum {string}
 */
chrome.passwordsPrivate.ExportProgressStatus = {
  NOT_STARTED: 'NOT_STARTED',
  IN_PROGRESS: 'IN_PROGRESS',
  SUCCEEDED: 'SUCCEEDED',
  FAILED_CANCELLED: 'FAILED_CANCELLED',
  FAILED_WRITE_FAILED: 'FAILED_WRITE_FAILED',
};

/**
 * @enum {string}
 */
chrome.passwordsPrivate.CompromiseType = {
  LEAKED: 'LEAKED',
  PHISHED: 'PHISHED',
  PHISHED_AND_LEAKED: 'PHISHED_AND_LEAKED',
};

/**
 * @enum {string}
 */
chrome.passwordsPrivate.PasswordCheckState = {
  IDLE: 'IDLE',
  RUNNING: 'RUNNING',
  CANCELED: 'CANCELED',
  OFFLINE: 'OFFLINE',
  SIGNED_OUT: 'SIGNED_OUT',
  NO_PASSWORDS: 'NO_PASSWORDS',
  QUOTA_LIMIT: 'QUOTA_LIMIT',
  OTHER_ERROR: 'OTHER_ERROR',
};

/**
 * @typedef {{
 *   origin: string,
 *   shown: string,
 *   link: string
 * }}
 */
chrome.passwordsPrivate.UrlCollection;

/**
 * @typedef {{
 *   urls: !chrome.passwordsPrivate.UrlCollection,
 *   username: string,
 *   federationText: (string|undefined),
 *   id: number,
 *   frontendId: number,
 *   fromAccountStore: boolean
 * }}
 */
chrome.passwordsPrivate.PasswordUiEntry;

/**
 * @typedef {{
 *   urls: !chrome.passwordsPrivate.UrlCollection,
 *   id: number,
 *   frontendId: number,
 *   fromAccountStore: boolean
 * }}
 */
chrome.passwordsPrivate.ExceptionEntry;

/**
 * @typedef {{
 *   status: !chrome.passwordsPrivate.ExportProgressStatus,
 *   folderName: (string|undefined)
 * }}
 */
chrome.passwordsPrivate.PasswordExportProgress;

/**
 * @typedef {{
 *   compromiseTime: number,
 *   elapsedTimeSinceCompromise: string,
 *   compromiseType: !chrome.passwordsPrivate.CompromiseType
 * }}
 */
chrome.passwordsPrivate.CompromisedInfo;

/**
 * @typedef {{
 *   id: number,
 *   formattedOrigin: string,
 *   detailedOrigin: string,
 *   isAndroidCredential: boolean,
 *   changePasswordUrl: (string|undefined),
 *   signonRealm: string,
 *   username: string,
 *   password: (string|undefined),
 *   compromisedInfo: (!chrome.passwordsPrivate.CompromisedInfo|undefined)
 * }}
 */
chrome.passwordsPrivate.InsecureCredential;

/**
 * @typedef {{
 *   state: !chrome.passwordsPrivate.PasswordCheckState,
 *   alreadyProcessed: (number|undefined),
 *   remainingInQueue: (number|undefined),
 *   elapsedTimeSinceLastCheck: (string|undefined)
 * }}
 */
chrome.passwordsPrivate.PasswordCheckStatus;

/**
 * Function that logs that the Passwords page was accessed from the Chrome
 * Settings WebUI.
 */
chrome.passwordsPrivate.recordPasswordsPageAccessInSettings = function() {};

/**
 * Changes the saved password corresponding to |ids|. Since the password can be
 * stored in Google Account and on device, in this case we want to change the
 * password for accountId and deviceId. Invokes |callback| or raises an error
 * depending on whether the operation succeeded.
 * @param {!Array<number>} ids The ids for the password entry being updated.
 * @param {string} new_username The new username.
 * @param {string} new_password The new password.
 * @param {function(): void=} callback The callback that gets invoked in the
 *     end.
 */
chrome.passwordsPrivate.changeSavedPassword = function(
    ids, new_username, new_password, callback) {};

/**
 * Removes the saved password corresponding to |id|. If no saved password for
 * this pair exists, this function is a no-op.
 * @param {number} id The id for the password entry being removed.
 */
chrome.passwordsPrivate.removeSavedPassword = function(id) {};

/**
 * Removes the saved password corresponding to |ids|. If no saved password
 * exists for a certain id, that id is ignored. Undoing this operation via
 * undoRemoveSavedPasswordOrException will restore all the removed passwords in
 * the batch.
 * @param {!Array<number>} ids
 */
chrome.passwordsPrivate.removeSavedPasswords = function(ids) {};

/**
 * Removes the saved password exception corresponding to |id|. If no exception
 * with this id exists, this function is a no-op.
 * @param {number} id The id for the exception url entry being removed.
 */
chrome.passwordsPrivate.removePasswordException = function(id) {};

/**
 * Removes the saved password exceptions corresponding to |ids|. If no exception
 * exists for a certain id, that id is ignored. Undoing this operation via
 * undoRemoveSavedPasswordOrException will restore all the removed exceptions in
 * the batch.
 * @param {!Array<number>} ids
 */
chrome.passwordsPrivate.removePasswordExceptions = function(ids) {};

/**
 * Undoes the last removal of saved password(s) or exception(s).
 */
chrome.passwordsPrivate.undoRemoveSavedPasswordOrException = function() {};

/**
 * Returns the plaintext password corresponding to |id|. Note that on some
 * operating systems, this call may result in an OS-level reauthentication. Once
 * the password has been fetched, it will be returned via |callback|.
 * @param {number} id The id for the password entry being being retrieved.
 * @param {!chrome.passwordsPrivate.PlaintextReason} reason The reason why the
 *     plaintext password is requested.
 * @param {function(string): void} callback The callback that gets invoked with
 *     the retrieved password.
 */
chrome.passwordsPrivate.requestPlaintextPassword = function(
    id, reason, callback) {};

/**
 * Returns the list of saved passwords.
 * @param {function(!Array<!chrome.passwordsPrivate.PasswordUiEntry>): void}
 *     callback Called with the list of saved passwords.
 */
chrome.passwordsPrivate.getSavedPasswordList = function(callback) {};

/**
 * Returns the list of password exceptions.
 * @param {function(!Array<!chrome.passwordsPrivate.ExceptionEntry>): void}
 *     callback Called with the list of password exceptions.
 */
chrome.passwordsPrivate.getPasswordExceptionList = function(callback) {};

/**
 * Moves a password currently stored on the device to being stored in the
 * signed-in, non-syncing Google Account. The result is a no-op if any of these
 * is true: |id| is invalid; |id| corresponds to a password already stored in
 * the account; or the user is not using the account-scoped password storage.
 * @param {number} id The id for the password entry being moved.
 */
chrome.passwordsPrivate.movePasswordToAccount = function(id) {};

/**
 * Triggers the Password Manager password import functionality.
 */
chrome.passwordsPrivate.importPasswords = function() {};

/**
 * Triggers the Password Manager password export functionality. Completion Will
 * be signaled by the onPasswordsFileExportProgress event. |callback| will be
 * called when the request is started or rejected. If rejected
 * $(ref:runtime.lastError) will be set to <code>'in-progress'</code> or
 * <code>'reauth-failed'</code>.
 * @param {function(): void} callback
 */
chrome.passwordsPrivate.exportPasswords = function(callback) {};

/**
 * Requests the export progress status. This is the same as the last value seen
 * on the onPasswordsFileExportProgress event. This function is useful for
 * checking if an export has already been initiated from an older tab, where we
 * might have missed the original event.
 * @param {function(!chrome.passwordsPrivate.ExportProgressStatus): void}
 *     callback
 */
chrome.passwordsPrivate.requestExportProgressStatus = function(callback) {};

/**
 * Stops exporting passwords and cleans up any passwords, which were already
 * written to the filesystem.
 */
chrome.passwordsPrivate.cancelExportPasswords = function() {};

/**
 * Requests the account-storage opt-in state of the current user.
 * @param {function(boolean): void} callback
 */
chrome.passwordsPrivate.isOptedInForAccountStorage = function(callback) {};

/**
 * Triggers the opt-in or opt-out flow for the account storage.
 * @param {boolean} optIn
 */
chrome.passwordsPrivate.optInForAccountStorage = function(optIn) {};

/**
 * Requests the latest compromised credentials.
 * @param {function(!Array<!chrome.passwordsPrivate.InsecureCredential>): void}
 *     callback
 */
chrome.passwordsPrivate.getCompromisedCredentials = function(callback) {};

/**
 * Requests the latest weak credentials.
 * @param {function(!Array<!chrome.passwordsPrivate.InsecureCredential>): void}
 *     callback
 */
chrome.passwordsPrivate.getWeakCredentials = function(callback) {};

/**
 * Requests the plaintext password for |credential|. |callback| gets invoked
 * with the same |credential|, whose |password| field will be set.
 * @param {!chrome.passwordsPrivate.InsecureCredential} credential The insecure
 *     credential whose password is being retrieved.
 * @param {!chrome.passwordsPrivate.PlaintextReason} reason The reason why the
 *     plaintext password is requested.
 * @param {function(!chrome.passwordsPrivate.InsecureCredential): void} callback
 *     The callback that gets invoked with the result.
 */
chrome.passwordsPrivate.getPlaintextInsecurePassword = function(
    credential, reason, callback) {};

/**
 * Requests to change the password of |credential| to |new_password|. Invokes
 * |callback| or raises an error depending on whether the operation succeeded.
 * @param {!chrome.passwordsPrivate.InsecureCredential} credential The
 *     credential whose password should be changed.
 * @param {string} new_password The new password.
 * @param {function(): void=} callback The callback that gets invoked in the
 *     end.
 */
chrome.passwordsPrivate.changeInsecureCredential = function(
    credential, new_password, callback) {};

/**
 * Requests to remove |credential| from the password store. Invokes |callback|
 * on completion.
 * @param {!chrome.passwordsPrivate.InsecureCredential} credential
 * @param {function(): void=} callback
 */
chrome.passwordsPrivate.removeInsecureCredential = function(
    credential, callback) {};

/**
 * Starts a check for insecure passwords. Invokes |callback| on completion.
 * @param {function(): void=} callback
 */
chrome.passwordsPrivate.startPasswordCheck = function(callback) {};

/**
 * Stops checking for insecure passwords. Invokes |callback| on completion.
 * @param {function(): void=} callback
 */
chrome.passwordsPrivate.stopPasswordCheck = function(callback) {};

/**
 * Returns the current status of the check via |callback|.
 * @param {function(!chrome.passwordsPrivate.PasswordCheckStatus): void}
 *     callback
 */
chrome.passwordsPrivate.getPasswordCheckStatus = function(callback) {};

/**
 * Fired when the saved passwords list has changed, meaning that an entry has
 * been added or removed.
 * @type {!ChromeEvent}
 */
chrome.passwordsPrivate.onSavedPasswordsListChanged;

/**
 * Fired when the password exceptions list has changed, meaning that an entry
 * has been added or removed.
 * @type {!ChromeEvent}
 */
chrome.passwordsPrivate.onPasswordExceptionsListChanged;

/**
 * Fired when the status of the export has changed.
 * @type {!ChromeEvent}
 */
chrome.passwordsPrivate.onPasswordsFileExportProgress;

/**
 * Fired when the opt-in state for the account-scoped storage has changed.
 * @type {!ChromeEvent}
 */
chrome.passwordsPrivate.onAccountStorageOptInStateChanged;

/**
 * Fired when the compromised credentials changed.
 * @type {!ChromeEvent}
 */
chrome.passwordsPrivate.onCompromisedCredentialsChanged;

/**
 * Fired when the weak credentials changed.
 * @type {!ChromeEvent}
 */
chrome.passwordsPrivate.onWeakCredentialsChanged;

/**
 * Fired when the status of the password check changes.
 * @type {!ChromeEvent}
 */
chrome.passwordsPrivate.onPasswordCheckStatusChanged;