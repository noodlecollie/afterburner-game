def options(opt):
	grp = opt.add_option_group("Gamelib options")

	grp.add_option("--enable-client-weapons", action = "store_true", dest = "CLIENT_WEAPONS", default = True,
		help = "Enable clientside weapon prediction [default: %default]")

def configure(conf):
	conf.env.append_unique("DEFINES", "GAME_LIBRARIES")

	if conf.options.CLIENT_WEAPONS:
		conf.define('CLIENT_WEAPONS', '1')

	if conf.env.DEST_OS == 'win32':
		conf.env.append_unique("DEFINES",
		[
			"_WIN32",
			"WIN32",
			"NOMINMAX"
		])

		# Needed to avoid warnings with MiniUTL.
		# 4005 = Macro redefinition
		# 4244 = Possible loss of data on type cast
		conf.env.append_unique("CXXFLAGS",
		[
			"/WX",
			"/wd4005",
			"/wd4244",
			"/EHsc"
		])
	else:
		conf.env.append_unique("DEFINES",
		[
			"_LINUX",	# Apparently this covers all non-Windows platforms adequately.
			"stricmp=strcasecmp",
			"strnicmp=strncasecmp",
			"_snprintf=snprintf",
			"_vsnprintf=vsnprintf"
		])

		conf.env.append_unique("CXXFLAGS",
		[
			"-fno-exceptions",
			"-Wno-invalid-offsetof"
		])
