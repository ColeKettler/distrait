#include <pebble.h>
#include "munge_time.h"

#define NUM_LINES 3
#define MAX_LINE_LENGTH 8
#define BUFFER_SIZE ((MAX_LINE_LENGTH + 1) * NUM_LINES)

static Window *window;
static TextLayer *display_layer;

static GFont display_font;

static char display_buffer[BUFFER_SIZE];

static void update_time() {
    // Get tm struct and local time.
    time_t t = time(NULL);
    struct tm *tick_time = localtime(&t);

    // Munge it.
    munge_time(tick_time->tm_hour, tick_time->tm_min, display_buffer, BUFFER_SIZE);

    text_layer_set_text(display_layer, display_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
}

static void window_load(Window *window) {
    // Window display.
    window_set_background_color(window, GColorBlack);

    // Time display.
    display_layer = text_layer_create(GRect(0, 4, 144, 168));
    text_layer_set_background_color(display_layer, GColorClear);
    text_layer_set_text_color(display_layer, GColorWhite);

    // Custom font.
    display_font = fonts_load_custom_font(
        resource_get_handle(RESOURCE_ID_BEBAS_NEUE_48));
    text_layer_set_font(display_layer, display_font);
    text_layer_set_text_alignment(display_layer, GTextAlignmentLeft);

    layer_add_child(window_get_root_layer(window),
                    text_layer_get_layer(display_layer));

    // Display initial time.
    update_time();
}

static void window_unload(Window *window) {
    fonts_unload_custom_font(display_font);
    text_layer_destroy(display_layer);
}

static void init() {
    window = window_create();

    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload
    });

    window_stack_push(window, true);

    // Subscribe to minute updates.
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
    window_destroy(window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
