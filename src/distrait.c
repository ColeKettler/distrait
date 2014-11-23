#include <pebble.h>

static Window *window;

static void update_time() {

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
}

static void window_load(Window *window) {
    // Display initial time.
    update_time();
}

static void window_unload(Window *window) {
    fonts_unload_custom_font(time_font);
    text_layer_destroy(time_layer);
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
