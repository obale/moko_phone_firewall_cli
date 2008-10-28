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
#include "../include/libphonefirewall.h"

#define VERSION "v0.01-alpha_xxxxxxxxxx"

int main(int argc, char **argv)
{

        if ( argc < 2 || 0 == strncmp(argv[1], "--help")
                      || 0 == strncmp(argv[1], "-h") ) {
                printf("Usage: %s [Option] [Parameter_1] ... [Parameter_n]\n", *argv);
                printf("Version: %s\n", VERSION);
                printf("Command line interface program for the phone firewall library.\n");
                printf("Helps you to manipulate the databases black- and whitelist.\n\n");

                printf("Option:\n");
                printf("add-black    Add a contact to the blacklist.\n");
                printf("             countrycode areacode number name reason priority.\n");
                printf("add-white    Add a contact to the whitelist.\n");
                printf("             countrycode areacode number name reason priority.\n\n");

                printf("Types of the parameters:\n");
                printf("countrycode  Integer     examples: 1, 2, 182, 99 ... \n");
                printf("areacode     Integer     examples: 1, 2, 182, 99 ...\n");
                printf("number       Big Integer examples: 1223787, 8793472 ...\n");
                printf("name         String      examples: \"Alex\", \"John Doe\" ...\n");
                printf("reason       String      examples: \"I don't like him\" ...\n");
                printf("priority     Integer     examples: 2, 10, 7, 3420 ...\n\n");

                printf("(c) MokSec Project [http://moksec.networld.to]\n");
        }

        int rc = -2;

        if ( 0 == strncmp(argv[1], "add-black") && 8 == argc ) {
                rc = add_entry(
                          atoi (argv[2]),       // countrycode
                          atoi (argv[3]),       // areacode
                          atoll(argv[4]),       // number
                                argv[5],        // name
                                argv[6],        // reason
                          atoi (argv[7]),       // priority
                          BLACKLIST_FLAG);      // listflag

        }

        else if ( 0 == strncmp(argv[1], "add-white") && 8 == argc ) {
                rc = add_entry(
                          atoi (argv[2]),       // countrycode
                          atoi (argv[3]),       // areacode
                          atoll(argv[4]),       // number
                                argv[5],        // name
                                argv[6],        // reason
                          atoi (argv[7]),       // priority
                          WHITELIST_FLAG);      // listflag
        }

        if      (  0 == rc ) printf("Entry added successfully.\n");
        else if ( -1 == rc ) printf("An error has occured.\n");

        return 0;
}
