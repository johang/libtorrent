/*

Copyright (c) 2003, Arvid Norberg
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#include <cstdlib>
#include "libtorrent/entry.hpp"
#include "libtorrent/bencode.hpp"
#include "libtorrent/session.hpp"
#include "libtorrent/torrent_info.hpp"

int main(int argc, char* argv[])
{
	using namespace lt;

	if (argc != 2)
	{
		fputs("usage: ./simple_client torrent-file\n"
			"to stop the client, press return.\n", stderr);
		return 1;
	}

	settings_pack sett;
	sett.set_str(settings_pack::listen_interfaces, "0.0.0.0:6881");
	lt::session s(sett);
	error_code ec;
	add_torrent_params p;
	p.save_path = "./";
	p.ti = std::make_shared<torrent_info>(std::string(argv[1]), std::ref(ec));
	if (ec)
	{
		std::fprintf(stderr, "%s\n", ec.message().c_str());
		return 1;
	}
	s.add_torrent(p, ec);
	if (ec)
	{
		std::fprintf(stderr, "%s\n", ec.message().c_str());
		return 1;
	}

	// wait for the user to end
	char a;
	int ret = std::scanf("%c\n", &a);
	(void)ret; // ignore
	return 0;
}

