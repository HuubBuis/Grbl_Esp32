#include "..\src\Grbl.h"

void report_macro_button(char* comment) {
    char          msg[80];
    const uint8_t offset = 4;  // ignore "MSG_" part of comment
    uint8_t       index  = offset;
    if (strstr(comment, "MSG")) {
        while (index < strlen(comment)) {
            msg[index - offset] = comment[index];
            index++;
        }
        msg[index - offset] = 0;  // null terminate
        grbl_msg_sendf(CLIENT_ALL, MsgLevel::Info, "CMD_%s", msg);
    }
}
void user_defined_macro(uint8_t index) {
    String user_macro;
    char   line[255];
    switch (index) {
        case 0:
            user_macro = user_macro0->get();
            break;
        case 1:
            user_macro = user_macro1->get();
            break;
        case 2:
            user_macro = user_macro2->get();
            break;
        case 3:
            user_macro = user_macro3->get();
            break;
        default:
            return;
    }

    if (user_macro == "") {
        grbl_msg_sendf(CLIENT_ALL, MsgLevel::Info, "Macro User/Macro%d empty", index);
        return;
    }

    user_macro.toCharArray(line, 255, 0);
    grbl_msg_sendf(CLIENT_ALL, MsgLevel::None, line);  // Report as is to be flexible
 }