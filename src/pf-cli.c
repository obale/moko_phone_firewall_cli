/*
 * pf-cli.c
 *
 * (C) 2008 by MokSec Project
 * Written by Alex Oberhauser <oberhauseralex@networld.to>
 * All Rights Reserved
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <libphonefirewall.h>

#define VERSION "v0.01-alpha"

/**
 * @mainfile
 * @file pf-cli.c
 * @author Alex Oberhauser
 * @brief Phone Firewall administration demo on the CLI
 *
 * This small cli program is a short demo how you could use the phone firewall
 * library to write your own programs. This examples demonstrates the administration
 * stuff.
 *
 * For the creation of the database (see logfile for location of the database
 *  under /tmp/phone-firewall.log or search of it) use the following script:
 *
 * -- *******************************************************************
 * --  phonefirewall: Script for creating black- and whitelist.
 * --  Usage:
 * --        $ sqlite3 db/phone-firewall.db < phonefirewall.sql
 * --
 * -- *******************************************************************
 * -- *******************************************************************
 * 
 * CREATE TABLE IF NOT EXISTS whitelist ( priority INTEGER,
 *                        countrycode INTEGER,
 *                        areacode INTEGER,
 *                        number BIGINT,
 *                        name varchar(64),
 *                        reason varchar(256),
 *                        PRIMARY KEY(countrycode, areacode, number) );
 *
 * CREATE TABLE IF NOT EXISTS blacklist ( priority INTEGER,
 *                        countrycode INTEGER,
 *                        areacode INTEGER,
 *                        number BIGINT,
 *                        name varchar(64),
 *                        reason varchar(256),
 *                        PRIMARY KEY(countrycode, areacode, number) )
 */
void print_entry(struct Entry *p_entry)
{
        int count = 1;
        printf("Nr.\tCountrycode\tAreacode\tNumber\tName\tReason");
        while ( p_entry != NULL ) {
                printf("#%d: +%d %d %llu - %s - %s\n", count,
                                                       p_entry->country_code,
                                                       p_entry->area_code,
                                                       p_entry->number,
                                                       p_entry->name,
                                                       p_entry->reason);
                p_entry = p_entry->next;
                count++;
        }
        printf("\n");
}

int main(int argc, char **argv)
{

        if ( argc < 2 || 0 == strcmp(argv[1], "--help")
                      || 0 == strcmp(argv[1], "-h") ) {
                printf("Usage: %s [Option] [Parameter_1] ... [Parameter_n]\n", *argv);
                printf("Version: %s\n", VERSION);
                printf("Command line interface program for the phone firewall library.\n");
                printf("Helps you to manipulate the databases black- and whitelist.\n\n");

                printf("Option:\n");
                printf("add-black    Add a contact to the blacklist. Parameters:\n");
                printf("             countrycode areacode number name reason priority\n");
                printf("add-white    Add a contact to the whitelist. Parameters:\n");
                printf("             countrycode areacode number name reason priority\n\n");

                printf("rm-black     Deletes a contact from the blacklist. Parameters:\n");
                printf("             countrycode areacode number\n");
                printf("rm-white     Deletes a contact from the whitelist. Parameters:\n");
                printf("             countrycode areacode number\n\n");

                printf("search-name-black     Search a entry by name in the blacklist. Parameters:\n");
                printf("                      name\n");
                printf("search-name-white     Search a entry by name in the whitelist. Parameters:\n");
                printf("                      name\n\n");

                printf("---------------------------------------------------------------------------\n");
                printf("Types of the parameters:\n");
                printf("countrycode  Integer     examples: 1, 2, 182, 99 ... \n");
                printf("areacode     Integer     examples: 1, 2, 182, 99 ...\n");
                printf("number       Big Integer examples: 1223787, 8793472 ...\n");
                printf("name         String      examples: \"Alex\", \"John Doe\" ...\n");
                printf("reason       String      examples: \"I don't like him\" ...\n");
                printf("priority     Integer     examples: 2, 10, 7, 3420 ...\n\n");

                printf("(c) MokSec Project [http://moksec.networld.to]\n");
        }

        char *action = "unknown";
        int rc = -2;
        struct Entry *p_entry;

        if ( 0 == strncmp(argv[1], "add-black") && 8 == argc ) {
                action = "add-black";
                rc = add_entry(
                          atoi (argv[2]),       // countrycode
                          atoi (argv[3]),       // areacode
                          atoll(argv[4]),       // number
                                argv[5],        // name
                                argv[6],        // reason
                          atoi (argv[7]),       // priority
                          BLACKLIST_FLAG);      // listflag

        } else if ( 0 == strncmp(argv[1], "add-white") && 8 == argc ) {
                action = "add-white";
                rc = add_entry(
                          atoi (argv[2]),       // countrycode
                          atoi (argv[3]),       // areacode
                          atoll(argv[4]),       // number
                                argv[5],        // name
                                argv[6],        // reason
                          atoi (argv[7]),       // priority
                          WHITELIST_FLAG);      // listflag
        } else if ( 0 == strncmp(argv[1], "rm-black") && 5 == argc ) {
                action = "rm-black";
                rc = rm_entry(
                          atoi (argv[2]),       // countrycode
                          atoi (argv[3]),       // areacode
                          atoll(argv[4]),       // number
                          BLACKLIST_FLAG);      // listflag
        } else if ( 0 == strncmp(argv[1], "rm-white") && 5 == argc ) {
                action = "rm-white";
                rc = rm_entry(
                          atoi (argv[2]),       // countrycode
                          atoi (argv[3]),       // areacode
                          atoll(argv[4]),       // number
                          WHITELIST_FLAG);      // listflag
        } else if ( 0 == strncmp(argv[1], "search-name-black") && 3 == argc ) {
                action = "search-name-black";
                p_entry = get_entry_by_name(
                          argv[2],              // name
                          BLACKLIST_FLAG);
                print_entry(p_entry);
        } else if ( 0 == strncmp(argv[1], "search-name-white") && 3 == argc ) {
                action = "search-name-white";
                p_entry = get_entry_by_name(
                          argv[2],              // name
                          WHITELIST_FLAG);
                print_entry(p_entry);
        }

        if      (  0 == rc ) printf("%s: successfully!\n", action);
        else if ( -1 == rc ) printf("%s: failed!\n", action);

        return 0;
}
