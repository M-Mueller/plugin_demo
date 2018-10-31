Example project for a plugin system
===================================

Intended as demo for https://github.com/probonopd/linuxdeployqt/issues/327

Install structure:

```
bin/demo
lib/libspam.so
lib/spam/libfoo.so
lib/spam/libbar.so
lib/spam/libbaz.so
```

Libraries in `lib/spam/` are consider plugins and are loaded dynamically during runtime by `libspam.so`.
