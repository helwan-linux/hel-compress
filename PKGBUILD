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
source=("$pkgname-$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
    cd "$pkgname-$pkgver"
    make
}

package() {
    cd "$pkgname-$pkgver"
    
    # تثبيت الملف التنفيذي
    install -Dm755 hel-compress "$pkgdir/usr/bin/hel-compress"
    
    # تثبيت ملف سطح المكتب (Desktop Entry) إذا وجد
    if [ -f "hel-compress.desktop" ]; then
        install -Dm644 hel-compress.desktop "$pkgdir/usr/share/applications/hel-compress.desktop"
    fi
    
    # تثبيت الأيقونة إذا وجدت
    if [ -f "icons/hel-compress.png" ]; then
        install -Dm644 icons/hel-compress.png "$pkgdir/usr/share/icons/hicolor/256x256/apps/hel-compress.png"
    fi
}
