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
    cd "$pkgname/$pkgname"
    make
}

package() {
    cd "$pkgname/$pkgname"
    
    # تثبيت ملف سطر الأوامر
    install -Dm755 hel-compress "$pkgdir/usr/bin/hel-compress"
    
    # تثبيت الواجهة الرسومية وتوحيد الاسم
    install -Dm755 hel-gui "$pkgdir/usr/bin/hel-gui"
    
    # تثبيت ملف سطح المكتب
    install -Dm644 hel-compress.desktop "$pkgdir/usr/share/applications/hel-compress.desktop"
    
    # تثبيت الأيقونة
    if [ -f "icons/hel-compress.png" ]; then
        install -Dm644 icons/hel-compress.png "$pkgdir/usr/share/icons/hicolor/256x256/apps/hel-compress.png"
    fi
}
