
#ifndef _SEAFILE_RPC_H
#define _SEAFILE_RPC_H

#include "seafile-object.h"

/**
 * seafile_get_session_info:
 *
 * Returns: a SeafileSessionInfo object.
 */
GObject *
seafile_get_session_info (GError **error);

/**
 * seafile_get_repo_list:
 *
 * Returns repository list.
 */
GList* seafile_get_repo_list (int start, int limit, const char *order_by, int ret_virt_repo, GError **error);

gint64
seafile_count_repos (GError **error);

/**
 * seafile_get_trash_repo_list:
 *
 * Returns deleted repository list.
 */
GList* seafile_get_trash_repo_list(int start, int limit, GError **error);

int
seafile_del_repo_from_trash (const char *repo_id, GError **error);

int
seafile_restore_repo_from_trash (const char *repo_id, GError **error);

GList *
seafile_get_trash_repos_by_owner (const char *owner, GError **error);

int
seafile_empty_repo_trash (GError **error);

int
seafile_empty_repo_trash_by_owner (const char *owner, GError **error);

/**
 * seafile_get_commit_list:
 *
 * @limit: if limit <= 0, all commits start from @offset will be returned.
 *
 * Returns: commit list of a given repo.
 *
 * Possible Error:
 *    1. Bad Argument
 *    2. No head and branch master
 *    3. Failed to list commits
 */
GList* seafile_get_commit_list (const gchar *repo,
                                int offset,
                                int limit,
                                GError **error);

/**
 * seafile_get_commit:
 * @id: the commit id.
 *
 * Returns: the commit object.
 */
GObject* seafile_get_commit (const char *repo_id, int version,
                             const gchar *id, GError **error);

/**
 * seafile_get_repo:
 *
 * Returns: repo
 */
GObject* seafile_get_repo (const gchar* id, GError **error);

GObject *
seafile_get_repo_sync_task (const char *repo_id, GError **error);

/**
 * seafile_get_repo_sync_info:
 */
GObject *
seafile_get_repo_sync_info (const char *repo_id, GError **error);

GList*
seafile_get_repo_sinfo (const char *repo_id, GError **error);

/* [seafile_get_config] returns the value of the config entry whose name is
 * [key] in config.db
 */
char *seafile_get_config (const char *key, GError **error);

/* [seafile_set_config] set the value of config key in config.db; old value
 * would be overwritten. */
int seafile_set_config (const char *key, const char *value, GError **error);

int
seafile_set_config_int (const char *key, int value, GError **error);

int
seafile_get_config_int (const char *key, GError **error);

int
seafile_set_upload_rate_limit (int limit, GError **error);

int
seafile_set_download_rate_limit (int limit, GError **error);

/**
 * seafile_destroy_repo:
 * @repo_id: repository id.
 */
int seafile_destroy_repo (const gchar *repo_id, GError **error);

int
seafile_unsync_repos_by_account (const char *server_addr, const char *email, GError **error);

int
seafile_remove_repo_tokens_by_account (const char *server_addr, const char *email, GError **error);

int
seafile_set_repo_token (const char *repo_id, const char *token, GError **error);

int
seafile_get_download_rate(GError **error);

int
seafile_get_upload_rate(GError **error);

/**
 * seafile_edit_repo:
 * @repo_id: repository id.
 * @name: new name of the repository, NULL if unchanged.
 * @description: new description of the repository, NULL if unchanged.
 */
int seafile_edit_repo (const gchar *repo_id, 
		       const gchar *name, 
		       const gchar *description,
                       const gchar *user,
		       GError **error);

int
seafile_change_repo_passwd (const char *repo_id,
                            const char *old_passwd,
                            const char *new_passwd,
                            const char *user,
                            GError **error);

int
seafile_upgrade_repo_pwd_hash_algorithm (const char *repo_id,
                                         const char *user,
                                         const char *passwd,
                                         const char *pwd_hash_algo,
                                         const char *pwd_hash_params,
                                         GError **error);

/**
 * seafile_repo_size:
 * 
 * Returns: the size of a repo
 *
 * Possible Error:
 *   1. Bad Argument
 *   2. No local branch (No local branch record in branch.db)
 *   3. Database error
 *   4. Calculate branch size error
 */
gint64
seafile_repo_size(const gchar *repo_id, GError **error);

int
seafile_repo_last_modify(const char *repo_id, GError **error);

int seafile_set_repo_lantoken (const gchar *repo_id,
                               const gchar *token,
                               GError **error);

gchar* seafile_get_repo_lantoken (const gchar *repo_id,
                                  GError **error);

int
seafile_set_repo_property (const char *repo_id,
                           const char *key,
                           const char *value,
                           GError **error);

gchar *
seafile_get_repo_property (const char *repo_id,
                           const char *key,
                           GError **error);

char *
seafile_get_repo_relay_address (const char *repo_id,
                                GError **error);

char *
seafile_get_repo_relay_port (const char *repo_id,
                             GError **error);

int
seafile_update_repo_relay_info (const char *repo_id,
                                const char *new_addr,
                                const char *new_port,
                                GError **error);

int
seafile_update_repos_server_host (const char *old_host,
                                  const char *new_host,
                                  const char *new_server_url,
                                  GError **error);

int seafile_disable_auto_sync (GError **error);

int seafile_enable_auto_sync (GError **error);

int seafile_is_auto_sync_enabled (GError **error);

char *
seafile_get_path_sync_status (const char *repo_id,
                              const char *path,
                              int is_dir,
                              GError **error);

int
seafile_mark_file_locked (const char *repo_id, const char *path, GError **error);

int
seafile_mark_file_unlocked (const char *repo_id, const char *path, GError **error);

char *
seafile_get_server_property (const char *server_url, const char *key, GError **error);

int
seafile_set_server_property (const char *server_url,
                             const char *key,
                             const char *value,
                             GError **error);

/**
 * seafile_list_dir:
 * List a directory.
 *
 * Returns: a list of dirents.
 * 
 * @limit: if limit <= 0, all dirents start from @offset will be returned.
 */
GList * seafile_list_dir (const char *repo_id,
                          const char *dir_id, int offset, int limit, GError **error);

/**
 * seafile_list_file_blocks:
 * List the blocks of a file.
 *
 * Returns: a list of block ids speprated by '\n'.
 * 
 * @limit: if limit <= 0, all blocks start from @offset will be returned.
 */
char * seafile_list_file_blocks (const char *repo_id,
                                 const char *file_id,
                                 int offset, int limit,
                                 GError **error);

/**
 * seafile_list_dir_by_path:
 * List a directory in a commit by the path of the directory.
 *
 * Returns: a list of dirents.
 */
GList * seafile_list_dir_by_path (const char *repo_id,
                                  const char *commit_id, const char *path, GError **error);

/**
 * seafile_get_dir_id_by_commit_and_path:
 * Get the dir_id of the path
 *
 * Returns: the dir_id of the path
 */
char * seafile_get_dir_id_by_commit_and_path (const char *repo_id,
                                              const char *commit_id,
                                              const char *path,
                                              GError **error);

/**
 * seafile_revert:
 * Reset the repo to a previous state by creating a new commit.
 */
int seafile_revert (const char *repo_id, const char *commit, GError **error);

char *
seafile_gen_default_worktree (const char *worktree_parent,
                              const char *repo_name,
                              GError **error);
int
seafile_check_path_for_clone(const char *path, GError **error);

/**
 * seafile_clone:
 *
 * Fetch a new repo and then check it out.
 */
char *
seafile_clone (const char *repo_id, 
               int repo_version,
               const char *peer_id,
               const char *repo_name,
               const char *worktree,
               const char *token,
               const char *passwd,
               const char *magic,
               const char *peer_addr,
               const char *peer_port,
               const char *email,
               const char *random_key,
               int enc_version,
               const char *more_info,
               GError **error);

char *
seafile_download (const char *repo_id, 
                  int repo_version,
                  const char *peer_id,
                  const char *repo_name,
                  const char *wt_parent,
                  const char *token,
                  const char *passwd,
                  const char *magic,
                  const char *peer_addr,
                  const char *peer_port,
                  const char *email,
                  const char *random_key,
                  int enc_version,
                  const char *more_info,
                  GError **error);

int
seafile_cancel_clone_task (const char *repo_id, GError **error);

int
seafile_remove_clone_task (const char *repo_id, GError **error);

/**
 * seafile_get_clone_tasks:
 *
 * Get a list of clone tasks.
 */
GList *
seafile_get_clone_tasks (GError **error);

/**
 * seafile_sync:
 *
 * Sync a repo with relay.
 */
int seafile_sync (const char *repo_id, const char *peer_id, GError **error);

/**
 * seafile_get_total_block_size:
 *
 * Get the sum of size of all the blocks.
 */
gint64
seafile_get_total_block_size (GError **error);


/**
 * seafile_get_commit_tree_block_number:
 *
 * Get the number of blocks belong to the commit tree.
 *
 * @commit_id: the head of the commit tree.
 *
 * Returns: -1 if the calculation is in progress, -2 if error, >=0 otherwise.
 */
int
seafile_get_commit_tree_block_number (const char *commit_id, GError **error);


/**
 * seafile_gc:
 * Start garbage collection.
 */
int
seafile_gc (GError **error);

/**
 * seafile_gc_get_progress:
 * Get progress of GC.
 *
 * Returns:
 *     progress of GC in precentage.
 *     -1 if GC is not running.
 */
/* int */
/* seafile_gc_get_progress (GError **error); */

/* -----------------  Task Related --------------  */

/**
 * seafile_find_transfer:
 *
 * Find a non finished task of a repo
 */
GObject *
seafile_find_transfer_task (const char *repo_id, GError *error);


int seafile_cancel_task (const gchar *task_id, int task_type, GError **error);

/**
 * Remove finished upload task
 */
int seafile_remove_task (const char *task_id, int task_type, GError **error);


/* ------------------ Relay specific RPC calls. ------------ */

/**
 * seafile_diff:
 *
 * Show the difference between @old commit and @new commit. If @old is NULL, then
 * show the difference between @new commit and its parent.
 *
 * @old and @new can also be branch name.
 */
GList *
seafile_diff (const char *repo_id, const char *old, const char *new,
              int fold_dir_results, GError **error);

GList *
seafile_branch_gets (const char *repo_id, GError **error);

/**
 * Return 1 if user is the owner of repo, otherwise return 0.
 */
int
seafile_is_repo_owner (const char *email, const char *repo_id,
                       GError **error);

int
seafile_set_repo_owner(const char *repo_id, const char *email,
                       GError **error);

/**
 * Return owner id of repo
 */
char *
seafile_get_repo_owner(const char *repo_id, GError **error);

GList *
seafile_get_orphan_repo_list(GError **error);

GList *
seafile_list_owned_repos (const char *email, int ret_corrupted, int start, int limit,
                          GError **error);

GList *
seafile_search_repos_by_name(const char *name, GError **error);

/**
 * seafile_add_chunk_server:
 * @server: ID for the chunk server.
 *
 * Add a chunk server on a relay server.
 */
int seafile_add_chunk_server (const char *server, GError **error);

/**
 * seafile_del_chunk_server:
 * @server: ID for the chunk server.
 *
 * Delete a chunk server on a relay server.
 */
int seafile_del_chunk_server (const char *server, GError **error);

/**
 * seafile_list_chunk_servers:
 *
 * List chunk servers set on a relay server.
 */
char *seafile_list_chunk_servers (GError **error);

gint64 seafile_get_user_quota_usage (const char *email, GError **error);

gint64 seafile_get_user_share_usage (const char *email, GError **error);

gint64
seafile_server_repo_size(const char *repo_id, GError **error);

int
seafile_repo_set_access_property (const char *repo_id, const char *ap,
                                  GError **error);

char *
seafile_repo_query_access_property (const char *repo_id, GError **error);

char *
seafile_web_get_access_token (const char *repo_id,
                              const char *obj_id,
                              const char *op,
                              const char *username,
                              int use_onetime,
                              GError **error);

GObject *
seafile_web_query_access_token (const char *token, GError **error);

char *
seafile_query_zip_progress (const char *token, GError **error);

int
seafile_cancel_zip_task (const char *token, GError **error);

GObject *
seafile_get_checkout_task (const char *repo_id, GError **error);

GList *
seafile_get_sync_task_list (GError **error);

char *
seafile_share_subdir_to_user (const char *repo_id,
                              const char *path,
                              const char *owner,
                              const char *share_user,
                              const char *permission,
                              const char *passwd,
                              GError **error);

int
seafile_unshare_subdir_for_user (const char *repo_id,
                                 const char *path,
                                 const char *owner,
                                 const char *share_user,
                                 GError **error);

int
seafile_update_share_subdir_perm_for_user (const char *repo_id,
                                           const char *path,
                                           const char *owner,
                                           const char *share_user,
                                           const char *permission,
                                           GError **error);

int
seafile_add_share (const char *repo_id, const char *from_email,
                   const char *to_email, const char *permission,
                   GError **error);

GList *
seafile_list_share_repos (const char *email, const char *type,
                          int start, int limit, GError **error);

GList *
seafile_list_repo_shared_to (const char *from_user, const char *repo_id,
                             GError **error);

GList *
seafile_list_repo_shared_group (const char *from_user, const char *repo_id,
                                GError **error);

int
seafile_remove_share (const char *repo_id, const char *from_email,
                      const char *to_email, GError **error);

char *
seafile_share_subdir_to_group (const char *repo_id,
                               const char *path,
                               const char *owner,
                               int share_group,
                               const char *permission,
                               const char *passwd,
                               GError **error);

int
seafile_unshare_subdir_for_group (const char *repo_id,
                                  const char *path,
                                  const char *owner,
                                  int share_group,
                                  GError **error);

int
seafile_update_share_subdir_perm_for_group (const char *repo_id,
                                            const char *path,
                                            const char *owner,
                                            int share_group,
                                            const char *permission,
                                            GError **error);

int
seafile_group_share_repo (const char *repo_id, int group_id,
                          const char *user_name, const char *permission,
                          GError **error);
int
seafile_group_unshare_repo (const char *repo_id, int group_id,
                            const char *user_name, GError **error);

/* Get groups that a repo is shared to */
char *
seafile_get_shared_groups_by_repo(const char *repo_id, GError **error);

char *
seafile_get_group_repoids (int group_id, GError **error);

GList *
seafile_get_repos_by_group (int group_id, GError **error);

GList *
seafile_get_group_repos_by_owner (char *user, GError **error);

char *
seafile_get_group_repo_owner (const char *repo_id, GError **error);

int
seafile_remove_repo_group(int group_id, const char *username, GError **error);

gint64
seafile_get_file_size (const char *store_id, int version,
                       const char *file_id, GError **error);

gint64
seafile_get_dir_size (const char *store_id, int version,
                      const char *dir_id, GError **error);

int
seafile_set_repo_history_limit (const char *repo_id,
                                int days,
                                GError **error);

int
seafile_get_repo_history_limit (const char *repo_id,
                                GError **error);

int
seafile_set_repo_valid_since (const char *repo_id,
                              gint64 timestamp,
                              GError **error);

int
seafile_check_passwd (const char *repo_id,
                      const char *magic,
                      GError **error);

int
seafile_set_passwd (const char *repo_id,
                    const char *user,
                    const char *passwd,
                    GError **error);

int
seafile_unset_passwd (const char *repo_id,
                      const char *user,
                      GError **error);

int
seafile_is_passwd_set (const char *repo_id, const char *user, GError **error);

GObject *
seafile_get_decrypt_key (const char *repo_id, const char *user, GError **error);

int
seafile_revert_on_server (const char *repo_id,
                          const char *commit_id,
                          const char *user_name,
                          GError **error);

/**
 * Add a file into the repo on server.
 * The content of the file is stored in a temporary file.
 * @repo_id: repo id
 * @temp_file_path: local file path, should be a temp file just uploaded.
 * @parent_dir: the parent directory to put the file in.
 * @file_name: the name of the target file.
 * @user: the email of the user who uploaded the file.
 */
int
seafile_post_file (const char *repo_id, const char *temp_file_path,
                  const char *parent_dir, const char *file_name,
                  const char *user,
                  GError **error);

/**
 * Add multiple files at once.
 *
 * @filenames_json: json array of filenames
 * @paths_json: json array of temp file paths
 */
char *
seafile_post_multi_files (const char *repo_id,
                          const char *parent_dir,
                          const char *filenames_json,
                          const char *paths_json,
                          const char *user,
                          int replace,
                          GError **error);

/**
 * Add file blocks at once.
 *
 * @blocks_json: json array of block ids
 * @paths_json: json array of temp file paths
 */
/* char * */
/* seafile_post_file_blocks (const char *repo_id, */
/*                           const char *parent_dir, */
/*                           const char *file_name, */
/*                           const char *blockids_json, */
/*                           const char *paths_json, */
/*                           const char *user, */
/*                           gint64 file_size, */
/*                           int replace_existed, */
/*                           GError **error); */


int
seafile_post_empty_file (const char *repo_id, const char *parent_dir,
                         const char *new_file_name, const char *user,
                         GError **error);

/**
 * Update an existing file in a repo
 * @params: same as seafile_post_file
 * @head_id: the commit id for the original file version.
 *           It's optional. If it's NULL, the current repo head will be used.
 * @return The new file id
 */
char *
seafile_put_file (const char *repo_id, const char *temp_file_path,
                  const char *parent_dir, const char *file_name,
                  const char *user, const char *head_id,
                  GError **error);

/**
 * Add file blocks at once.
 *
 * @blocks_json: json array of block ids
 * @paths_json: json array of temp file paths
 */
/* char * */
/* seafile_put_file_blocks (const char *repo_id, const char *parent_dir, */
/*                          const char *file_name, const char *blockids_json, */
/*                          const char *paths_json, const char *user, */
/*                          const char *head_id, gint64 file_size, GError **error); */


int
seafile_post_dir (const char *repo_id, const char *parent_dir,
                  const char *new_dir_name, const char *user,
                  GError **error);
int
seafile_mkdir_with_parents (const char *repo_id, const char *parent_dir,
                            const char *new_dir_path, const char *user,
                            GError **error);

/**
 * delete a file/directory from the repo on server.
 * @repo_id: repo id
 * @parent_dir: the parent directory of the file to be deleted
 * @file_name: the name of the target file.
 * @user: the email of the user who uploaded the file.
 */
int
seafile_del_file (const char *repo_id, 
                  const char *parent_dir, const char *file_name,
                  const char *user,
                  GError **error);

int
seafile_batch_del_files (const char *repo_id,
                         const char *file_list,
                         const char *user,
                         GError **error);

/**
 * copy a file/directory from a repo to another on server.
 */
GObject *
seafile_copy_file (const char *src_repo_id,
                   const char *src_dir,
                   const char *src_filename,
                   const char *dst_repo_id,
                   const char *dst_dir,
                   const char *dst_filename,
                   const char *user,
                   int need_progress,
                   int synchronous,
                   GError **error);


GObject *
seafile_move_file (const char *src_repo_id,
                   const char *src_dir,
                   const char *src_filename,
                   const char *dst_repo_id,
                   const char *dst_dir,
                   const char *dst_filename,
                   int replace,
                   const char *user,
                   int need_progress,
                   int synchronous,
                   GError **error);

GObject *
seafile_get_copy_task (const char *task_id, GError **error);

int
seafile_cancel_copy_task (const char *task_id, GError **error);

int
seafile_rename_file (const char *repo_id,
                     const char *parent_dir,
                     const char *oldname,
                     const char *newname,
                     const char *user,
                     GError **error);

/**
 * Return non-zero if filename is valid.
 */
int
seafile_is_valid_filename (const char *repo_id,
                           const char *filename,
                           GError **error);


int
seafile_set_user_quota (const char *user, gint64 quota, GError **error);

gint64
seafile_get_user_quota (const char *user, GError **error);

int
seafile_check_quota (const char *repo_id, gint64 delta, GError **error);

GList *
seafile_list_user_quota_usage (GError **error);

char *
seafile_get_file_id_by_path (const char *repo_id, const char *path,
                             GError **error);

char *
seafile_get_dir_id_by_path (const char *repo_id, const char *path,
                            GError **error);

GObject *
seafile_get_dirent_by_path (const char *repo_id, const char *path,
                            GError **error);

/**
 * Return a list of commits where every commit contains a unique version of
 * the file.
 */
GList *
seafile_list_file_revisions (const char *repo_id,
                             const char *commit_id,
                             const char *path,
                             int limit,
                             GError **error);

GList *
seafile_calc_files_last_modified (const char *repo_id,
                                  const char *parent_dir,
                                  int limit,
                                  GError **error);

int
seafile_revert_file (const char *repo_id,
                     const char *commit_id,
                     const char *path,
                     const char *user,
                     GError **error);

int
seafile_revert_dir (const char *repo_id,
                    const char *commit_id,
                    const char *path,
                    const char *user,
                    GError **error);

char *
seafile_check_repo_blocks_missing (const char *repo_id,
                                   const char *blockids_json,
                                   GError **error);

/*
 * @show_days: return deleted files in how many days, return all if 0.
 */
GList *
seafile_get_deleted (const char *repo_id, int show_days,
                     const char *path, const char *scan_stat,
                     int limit, GError **error);

/**
 * Generate a new token for (repo_id, email) and return it
 */
char *
seafile_generate_repo_token (const char *repo_id,
                             const char *email,
                             GError **error);

int
seafile_delete_repo_token (const char *repo_id,
                           const char *token,
                           const char *user,
                           GError **error);

GList *
seafile_list_repo_tokens (const char *repo_id,
                          GError **error);

GList *
seafile_list_repo_tokens_by_email (const char *email,
                                   GError **error);

int
seafile_delete_repo_tokens_by_peer_id(const char *email, const char *peer_id, GError **error);

int
seafile_delete_repo_tokens_by_email (const char *email,
                                     GError **error);

/**
 * create a repo on seahub
 */
char *
seafile_create_repo (const char *repo_name,
                     const char *repo_desc,
                     const char *owner_email,
                     const char *passwd,
                     int enc_version,
                     const char *pwd_hash_algo,
                     const char *pwd_hash_params,
                     GError **error);

char *
seafile_create_enc_repo (const char *repo_id,
                         const char *repo_name,
                         const char *repo_desc,
                         const char *owner_email,
                         const char *magic,
                         const char *random_key,
                         const char *salt,
                         int enc_version,
                         const char *pwd_hash,
                         const char *pwd_hash_algo,
                         const char *pwd_hash_params,
                         GError **error);

char *
seafile_check_permission (const char *repo_id, const char *user, GError **error);

char *
seafile_check_permission_by_path (const char *repo_id, const char *path,
                                  const char *user, GError **error);

GList *
seafile_list_dir_with_perm (const char *repo_id,
                            const char *path,
                            const char *dir_id,
                            const char *user,
                            int offset,
                            int limit,
                            GError **error);

int
seafile_set_inner_pub_repo (const char *repo_id,
                            const char *permission,
                            GError **error);

int
seafile_unset_inner_pub_repo (const char *repo_id, GError **error);

GList *
seafile_list_inner_pub_repos (GError **error);

gint64
seafile_count_inner_pub_repos (GError **error);

GList *
seafile_list_inner_pub_repos_by_owner (const char *user, GError **error);

int
seafile_is_inner_pub_repo (const char *repo_id, GError **error);

int
seafile_set_share_permission (const char *repo_id,
                              const char *from_email,
                              const char *to_email,
                              const char *permission,
                              GError **error);

int
seafile_set_group_repo_permission (int group_id,
                                   const char *repo_id,
                                   const char *permission,
                                   GError **error);

char *
seafile_get_file_id_by_commit_and_path(const char *repo_id,
                                       const char *commit_id,
                                       const char *path,
                                       GError **error);

/* virtual repo related */

char *
seafile_create_virtual_repo (const char *origin_repo_id,
                             const char *path,
                             const char *repo_name,
                             const char *repo_desc,
                             const char *owner,
                             const char *passwd,
                             GError **error);

GList *
seafile_get_virtual_repos_by_owner (const char *owner, GError **error);

GObject *
seafile_get_virtual_repo (const char *origin_repo,
                          const char *path,
                          const char *owner,
                          GError **error);

char *
seafile_get_system_default_repo_id (GError **error);

/* Clean trash */

int
seafile_clean_up_repo_history (const char *repo_id, int keep_days, GError **error);

/* ------------------ public RPC calls. ------------ */

GList* seafile_get_repo_list_pub (int start, int limit, GError **error);

GObject* seafile_get_repo_pub (const gchar* id, GError **error);

GList* seafile_get_commit_list_pub (const gchar *repo,
                                    int offset,
                                    int limit,
                                    GError **error);

GObject* seafile_get_commit_pub (const gchar *id, GError **error);

char *seafile_diff_pub (const char *repo_id, const char *old, const char *new,
                        GError **error);

GList * seafile_list_dir_pub (const char *dir_id, GError **error);

GList *
seafile_get_shared_users_for_subdir (const char *repo_id,
                                     const char *path,
                                     const char *from_user,
                                     GError **error);
GList *
seafile_get_shared_groups_for_subdir (const char *repo_id,
                                      const char *path,
                                      const char *from_user,
                                      GError **error);
GObject *
seafile_generate_magic_and_random_key(int enc_version,
                                      const char* repo_id,
                                      const char *passwd,
                                      GError **error);

gint64
seafile_get_total_file_number (GError **error);

gint64
seafile_get_total_storage (GError **error);

GObject *
seafile_get_file_count_info_by_path (const char *repo_id,
                                     const char *path,
                                     GError **error);

char *
seafile_get_trash_repo_owner (const char *repo_id, GError **error);

int
seafile_set_server_config_int (const char *group, const char *key, int value, GError **error);

int
seafile_get_server_config_int (const char *group, const char *key, GError **error);

int
seafile_set_server_config_int64 (const char *group, const char *key, gint64 value, GError **error);

gint64
seafile_get_server_config_int64 (const char *group, const char *key, GError **error);

int
seafile_set_server_config_string (const char *group, const char *key, const char *value, GError **error);

char *
seafile_get_server_config_string (const char *group, const char *key, GError **error);

int
seafile_set_server_config_boolean (const char *group, const char *key, int value, GError **error);

int
seafile_get_server_config_boolean (const char *group, const char *key, GError **error);

GObject *
seafile_get_group_shared_repo_by_path (const char *repo_id,
                                       const char *path,
                                       int group_id,
                                       int is_org,
                                       GError **error);

GObject *
seafile_get_shared_repo_by_path (const char *repo_id,
                                 const char *path,
                                 const char *shared_to,
                                 int is_org,
                                 GError **error);

GList *
seafile_get_group_repos_by_user (const char *user, GError **error);

GList *
seafile_get_org_group_repos_by_user (const char *user, int org_id, GError **error);

int
seafile_repo_has_been_shared (const char *repo_id, int including_groups, GError **error);

GList *
seafile_get_shared_users_by_repo (const char *repo_id, GError **error);

GList *
seafile_org_get_shared_users_by_repo (int org_id,
                                      const char *repo_id,
                                      GError **error);

gint64
seafile_get_upload_tmp_file_offset (const char *repo_id, const char *file_path,
                                    GError **error);

char *
seafile_convert_repo_path (const char *repo_id,
                           const char *path,
                           const char *user,
                           int is_org,
                           GError **error);

int
seafile_set_repo_status(const char *repo_id, int status, GError **error);

int
seafile_get_repo_status(const char *repo_id, GError **error);

GList*
seafile_get_repos_by_id_prefix  (const char *id_prefix, int start,
                                 int limit, GError **error);

int
seafile_publish_event(const char *channel, const char *content, GError **error);

json_t *
seafile_pop_event(const char *channel, GError **error);

GList *
seafile_search_files (const char *repo_id, const char *str, GError **error);

GList *
seafile_search_files_by_path (const char *repo_id, const char *path, const char *str, GError **error);

/*Following is ccnet rpc*/
int
ccnet_rpc_add_emailuser (const char *email, const char *passwd,
                         int is_staff, int is_active, GError **error);

int
ccnet_rpc_remove_emailuser (const char *source, const char *email, GError **error);

int
ccnet_rpc_validate_emailuser (const char *email, const char *passwd, GError **error);

GObject*
ccnet_rpc_get_emailuser (const char *email, GError **error);

GObject*
ccnet_rpc_get_emailuser_with_import (const char *email, GError **error);

GObject*
ccnet_rpc_get_emailuser_by_id (int id, GError **error);

GList*
ccnet_rpc_get_emailusers (const char *source, int start, int limit, const char *status, GError **error);

GList*
ccnet_rpc_search_emailusers (const char *source,
                             const char *email_patt,
                             int start, int limit,
                             GError **error);

GList*
ccnet_rpc_search_ldapusers (const char *keyword,
                            int start, int limit,
                            GError **error);

/* Get total counts of email users. */
gint64
ccnet_rpc_count_emailusers (const char *source, GError **error);

gint64
ccnet_rpc_count_inactive_emailusers (const char *source, GError **error);

int
ccnet_rpc_update_emailuser (const char *source, int id, const char* passwd,
                            int is_staff, int is_active,
                            GError **error);

int
ccnet_rpc_update_role_emailuser (const char* email, const char* role, GError **error);

GList*
ccnet_rpc_get_superusers (GError **error);

GList *
ccnet_rpc_get_emailusers_in_list(const char *source, const char *user_list, GError **error);

int
ccnet_rpc_update_emailuser_id (const char *old_email, const char *new_email, GError **error);

int
ccnet_rpc_create_group (const char *group_name, const char *user_name,
                        const char *type, int parent_group_id, GError **error);

int
ccnet_rpc_create_org_group (int org_id, const char *group_name,
                            const char *user_name, int parent_group_id, GError **error);

int
ccnet_rpc_remove_group (int group_id, GError **error);

int
ccnet_rpc_group_add_member (int group_id, const char *user_name,
                            const char *member_name, GError **error);
int
ccnet_rpc_group_remove_member (int group_id, const char *user_name,
                               const char *member_name, GError **error);

int
ccnet_rpc_group_set_admin (int group_id, const char *member_name,
                           GError **error);

int
ccnet_rpc_group_unset_admin (int group_id, const char *member_name,
                           GError **error);

int
ccnet_rpc_set_group_name (int group_id, const char *group_name,
                          GError **error);

int
ccnet_rpc_quit_group (int group_id, const char *user_name, GError **error);

GList *
ccnet_rpc_get_groups (const char *username, int return_ancestors, GError **error);

GList *
ccnet_rpc_list_all_departments (GError **error);

GList *
ccnet_rpc_get_all_groups (int start, int limit, const char *source, GError **error);

GList *
ccnet_rpc_get_ancestor_groups (int group_id, GError **error);

GList *
ccnet_rpc_get_top_groups (int including_org, GError **error);

GList *
ccnet_rpc_get_child_groups (int group_id, GError **error);

GList *
ccnet_rpc_get_descendants_groups(int group_id, GError **error);

GObject *
ccnet_rpc_get_group (int group_id, GError **error);

GList *
ccnet_rpc_get_group_members (int group_id, int start, int limit, GError **error);

GList *
ccnet_rpc_get_members_with_prefix(int group_id, const char *prefix, GError **error);

int
ccnet_rpc_check_group_staff (int group_id, const char *user_name, int in_structure,
                             GError **error);

int
ccnet_rpc_remove_group_user (const char *user, GError **error);

int
ccnet_rpc_is_group_user (int group_id, const char *user, int in_structure, GError **error);

int
ccnet_rpc_set_group_creator (int group_id, const char *user_name,
                             GError **error);

GList*
ccnet_rpc_search_groups (const char *group_patt,
                         int start, int limit,
                         GError **error);

GList *
ccnet_rpc_get_groups_members (const char *group_ids, GError **error);

GList *
ccnet_rpc_search_group_members (int group_id, const char *pattern, GError **error);

int
ccnet_rpc_create_org (const char *org_name, const char *url_prefix,
                      const char *creator, GError **error);

int
ccnet_rpc_remove_org (int org_id, GError **error);

GList *
ccnet_rpc_get_all_orgs (int start, int limit, GError **error);

gint64
ccnet_rpc_count_orgs (GError **error);

GObject *
ccnet_rpc_get_org_by_url_prefix (const char *url_prefix, GError **error);

GObject *
ccnet_rpc_get_org_by_id (int org_id, GError **error);

int
ccnet_rpc_add_org_user (int org_id, const char *email, int is_staff,
                        GError **error);

int
ccnet_rpc_remove_org_user (int org_id, const char *email, GError **error);

GList *
ccnet_rpc_get_orgs_by_user (const char *email, GError **error);

GList *
ccnet_rpc_get_org_emailusers (const char *url_prefix, int start , int limit,
                              GError **error);

int
ccnet_rpc_add_org_group (int org_id, int group_id, GError **error);

int
ccnet_rpc_remove_org_group (int org_id, int group_id, GError **error);

int
ccnet_rpc_is_org_group (int group_id, GError **error);

int
ccnet_rpc_get_org_id_by_group (int group_id, GError **error);

GList *
ccnet_rpc_get_org_groups (int org_id, int start, int limit, GError **error);

GList *
ccnet_rpc_get_org_groups_by_user (const char *user, int org_id, GError **error);

GList *
ccnet_rpc_get_org_top_groups (int org_id, GError **error);

int
ccnet_rpc_org_user_exists (int org_id, const char *email, GError **error);

int
ccnet_rpc_is_org_staff (int org_id, const char *email, GError **error);

int
ccnet_rpc_set_org_staff (int org_id, const char *email, GError **error);

int
ccnet_rpc_unset_org_staff (int org_id, const char *email, GError **error);

int
ccnet_rpc_set_org_name (int org_id, const char *org_name, GError **error);

int
ccnet_rpc_set_reference_id (const char *primary_id, const char *reference_id, GError **error);

char *
ccnet_rpc_get_primary_id (const char *email, GError **error);

#endif
