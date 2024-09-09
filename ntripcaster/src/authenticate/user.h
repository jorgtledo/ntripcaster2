/*
 * user.h
 * - Function definitions for user.c
 *
 * Copyright (c) 2003
 * German Federal Agency for Cartography and Geodesy (BKG)
 *
 * Developed for Networked Transport of RTCM via Internet Protocol (NTRIP)
 * for streaming GNSS data over the Internet.
 *
 * Designed by Informatik Centrum Dortmund http://www.icd.de
 *
 * The BKG disclaims any liability nor responsibility to any person or entity
 * with respect to any loss or damage caused, or alleged to be caused,
 * directly or indirectly by the use and application of the NTRIP technology.
 *
 * For latest information and updates, access:
 * http://igs.ifag.de/index_ntrip.htm
 *
 * Georg Weber
 * BKG, Frankfurt, Germany, June 2003-06-13
 * E-mail: euref-ip@bkg.bund.de
 *
 * Based on the GNU General Public License published Icecast 1.3.12
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

void parse_user_authentication_file();
void parse_ban_file();
ntripcaster_user_t *create_user_from_line(char *line);
ntripcaster_ban_t *create_ban_from_line(char *line);
ntripcaster_user_t *create_user();
ntripcaster_ban_t *create_ban();
void add_authentication_user(ntripcaster_user_t * user);
void add_ban_user(ntripcaster_ban_t * ban);
usertree_t *create_user_tree();
bantree_t *create_ban_tree();
void free_user_tree(usertree_t * ut);
void free_ban_tree(bantree_t * bt);
int user_authenticate(char *cuser, const char *password);
int ban_check(char *ip);
ntripcaster_user_t *find_user_from_tree(usertree_t * ut, char *name);
ntripcaster_user_t *con_get_user(connection_t * con);
void con_display_users(com_request_t * req);
void html_display_users(com_request_t *req);
int runtime_add_user(char *name, char *password);
int get_ban_count();
