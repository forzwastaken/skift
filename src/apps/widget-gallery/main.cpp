#include <karm-main/main.h>
#include <karm-ui/align.h>
#include <karm-ui/app.h>
#include <karm-ui/button.h>
#include <karm-ui/flow.h>
#include <karm-ui/scafold.h>

void nop() {}

Ui::Child buttons() {
    return Ui::vflow(
        8,
        Ui::titlebar(Media::Icons::DUCK, String{"Widget Gallery"}),
        Ui::button(nop, Ui::Button::PRIMARY, "PRIMARY BUTTON"),
        Ui::button(nop, "BUTTON"),
        Ui::button(nop, Ui::Button::OUTLINE, "OUTLINE BUTTON"),
        Ui::button(nop, Ui::Button::SUBTLE, "SUBTLE BUTTON"),
        Ui::button(nop, Ui::Button::DESTRUCTIVE, "DESTRUCTIVE BUTTON"));
}

Ui::Child texts() {
    auto fontface = Media::loadFontface("res/fonts/inter/Inter-Regular.ttf").unwrap();
    return Ui::vflow(
        8,
        Ui::text(Media::Font{12, fontface}, "The quick brown fox jumps over the lazy dog."),
        Ui::text(Media::Font{14, fontface}, "The quick brown fox jumps over the lazy dog."),
        Ui::text(Media::Font{18, fontface}, "The quick brown fox jumps over the lazy dog."),
        Ui::text(Media::Font{22, fontface}, "The quick brown fox jumps over the lazy dog."),
        Ui::text(Media::Font{36, fontface}, "The quick brown fox jumps over the lazy dog."),
        Ui::text(Media::Font{48, fontface}, "The quick brown fox jumps over the lazy dog."));
}

CliResult entryPoint(CliArgs args) {
    Ui::App app([]() {
        return Ui::spacing(
            8,
            buttons());
    });

    return app.run(args);
}
