set architecture aarch64
set target-charset UTF-16
handle SIGXCPU SIG33 SIG35 SIGPWR nostop noprint

source libs/arm64-v8a/gdb.setup

define csstr_print
p &$arg0->m_firstChar
end
