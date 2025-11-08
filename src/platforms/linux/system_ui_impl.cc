#include "system_ui_impl.h"
#include <libruntime.h>
#include <random>
#include <adwaita.h>
#include <gtk-4.0/gtk/gtk.h>

std::mutex LinuxSystemUI::dialog_present_status_mutex_ = std::mutex();
std::map<unsigned long, bool> LinuxSystemUI::dialog_present_status_ = std::map<unsigned long, bool>();
std::thread LinuxSystemUI::gtk_work_thread_;
GtkApplication* LinuxSystemUI::gtk_app_ = nullptr;
bool LinuxSystemUI::gtk_app_quit_required_ = false;

LinuxSystemUI::LinuxSystemUI() {
    if (gtk_app_ == nullptr) {
        gtk_work_thread_ = std::thread([&] {
            adw_init();
            gtk_app_ = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
            while (!gtk_app_quit_required_) {
                g_main_context_iteration(nullptr, true);
            }
        });
    }
}

LinuxSystemUI::~LinuxSystemUI() {
    gtk_app_quit_required_ = true;
    gtk_work_thread_.join();
}

void LinuxSystemUI::show_dialog(const ttstr& title, const ttstr& message) {
    std::string title_out;
    std::string message_out;
    TVPUtf16ToUtf8(title_out, title.c_str());
    TVPUtf16ToUtf8(message_out, message.c_str());

    auto dialog_id = generate_dialog_id();
    dialog_present_status_mutex_.lock();
    dialog_present_status_[dialog_id] = true;
    dialog_present_status_mutex_.unlock();

    g_idle_add([](gpointer data) -> gboolean {
        const auto* dialog_data = static_cast<DialogData*>(data);

        const auto dialog = gtk_alert_dialog_new(dialog_data->title.c_str());
        gtk_alert_dialog_set_message(dialog, dialog_data->title.c_str());
        gtk_alert_dialog_set_detail(dialog, dialog_data->message.c_str());

        gtk_alert_dialog_choose(dialog, nullptr, nullptr, +[](GObject *source_object, GAsyncResult *res, gpointer data) {
            dialog_present_status_mutex_.lock();
            dialog_present_status_[*static_cast<unsigned long *>(data)] = false;
            dialog_present_status_mutex_.unlock();
            gtk_alert_dialog_choose_finish(GTK_ALERT_DIALOG(source_object), res, nullptr);
            delete static_cast<unsigned long*>(data);
        }, new unsigned long(dialog_data->dialog_id));

        delete dialog_data;
        return G_SOURCE_REMOVE; // 一度だけ実行
    }, new DialogData{title_out, message_out, dialog_id});

    while (dialog_present_status_[dialog_id]) {
        usleep(0.5 * 1000000);
    }
}

void LinuxSystemUI::show_version_dialog()
{
    g_idle_add([](gpointer data) -> gboolean {
        const auto* dialog_data = static_cast<DialogData*>(data);

        auto about_text = LibRuntime::KrkrRuntime::get_about_text();
        std::string about_text_out;
        TVPUtf16ToUtf8(about_text_out, about_text.c_str());

        ttstr version_text;
        std::string version_text_out;
        LibRuntime::KrkrRuntime::get_runtime_version_full(version_text);
        TVPUtf16ToUtf8(version_text_out, version_text.c_str());

        gtk_show_about_dialog(nullptr,
            "program-name", "吉里吉里X",
            "title", "吉里吉里X",
            "version", version_text_out.c_str(),
            "license-type", GTK_LICENSE_APACHE_2_0,
            "system-information", about_text_out.c_str());
        delete dialog_data;
        return G_SOURCE_REMOVE; // 一度だけ実行
    }, new DialogData{"nullptr", "", 0});
}

unsigned long LinuxSystemUI::generate_dialog_id() {
    std::random_device seed_gen;
    auto mt_generator = std::mt19937(seed_gen());
    return mt_generator();
}
