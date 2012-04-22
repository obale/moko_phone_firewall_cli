###########################################################################
# Makefile for phonefirewall command line interface (cli)
#
# (C) 2008 by MokSec Project
# Written by Alex Oberhauser <oberhauseralex@networld.to>
# All Rights Reserved
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>
###########################################################################
RM = /bin/rm
CLFLAGS += --std=c99 -Wall -Werror -DDEBUG -g -o -O0
LIB = -lsqlite3 -lphonefirewall
DOXYGEN = /usr/bin/doxygen
SRCDIR = src
BINDIR = bin
INCLUDEDIR = include

all: pf-cli

pf-cli.o: $(SRCDIR)/pf-cli.c $(INCLUDEDIR)/libphonefirewall.h
	$(CC) $(CLFLAGS) -c $(SRCDIR)/pf-cli.c -o $(SRCDIR)/$@

pf-cli: $(SRCDIR)/pf-cli.o
	$(CC) $(CLFLAGS) $(LIB) $(SRCDIR)/pf-cli.o -o $(BINDIR)/$@

.PHONY: clean
clean:
	$(RM) -f $(BINDIR)/*\
                 $(SRCDIR)/*.o
