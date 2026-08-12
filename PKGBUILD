# Maintainer: Saeed Badreldin <saeed@helwanlinux.org>
pkgname=hel-compress
pkgver=1.0.0
pkgrel=1
pkgdesc="Advanced compression and archiving tool with support for multiple algorithms, encryption, and GUI"
arch=('x86_64')
url="https://github.com/helwan-linux/hel-compress"
license=('MIT')
depends=('zlib' 'bzip2' 'zstd' 'openssl' 'gtk3')
makedepends=('gcc' 'make' 'pkgconfig')
source=("git+https://github.com/helwan-linux/hel-compress.git")
sha256sums=('SKIP')

build() {
    cd "$pkgname"
    make
}

package() {
    cd "$pkgname"
    
    # تثبيت الملف التنفيذي للـ CLI
    install -Dm755 hel-compress "$pkgdir/usr/bin/hel-compress"
    
    # تثبيت الملف التنفيذي للـ GUI (إذا تم بناؤه كملف منفصل أو أداة مستقلة)
    if [ -f "hel-gui" ]; then
        install -Dm755 hel-gui "$pkgdir/usr/bin/hel-gui"
    fi
    
    # تثبيت ملف سطح المكتب (Desktop Entry)
    if [ -f "hel-compress.desktop" ]; then
        install -Dm644 hel-compress.desktop "$pkgdir/usr/share/applications/hel-compress.desktop"
    fi
    
    # تثبيت الأيقونة
    if [ -f "icons/hel-compress.png" ]; then
        install -Dm644 icons/hel-compress.png "$pkgdir/usr/share/icons/hicolor/256x256/apps/hel-compress.png"
    fi
}
