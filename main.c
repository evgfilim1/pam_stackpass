#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <string.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t* pamh, int flags, int argc, const char** argv) {
    // Parse args
    const char* prompt = NULL;
    enum { OP_UNKNOWN = -1, OP_PROMPT, OP_ECHO } op_mode = OP_UNKNOWN;
    for (int i = 0; i < argc; i++) {
        if (!strncmp(argv[i], "prompt", 6)) {
            prompt = "Verification code or password: ";
            if (op_mode != OP_UNKNOWN) {
                pam_error(pamh, "Multiple operations specified!\nUsage: libpam_stackpass.so <prompt|echo>\n");
                return PAM_SERVICE_ERR;
            }
            op_mode = OP_PROMPT;
        } else if (!strncmp(argv[i], "echo", 4)) {
            prompt = "Stacked auth token: ";
            if (op_mode != OP_UNKNOWN) {
                pam_error(pamh, "Multiple operations specified!\nUsage: libpam_stackpass.so <prompt|echo>\n");
                return PAM_SERVICE_ERR;
            }
            op_mode = OP_ECHO;
        }
    }
    // Process
    char* authtok = NULL;
    int res;
    switch (op_mode) {
        case OP_UNKNOWN:
            pam_error(pamh, "No known operation was specified!\nUsage: libpam_stackpass.so <prompt|echo>\n");
            return PAM_NO_MODULE_DATA;
        case OP_PROMPT:
            res = pam_prompt(pamh, PAM_PROMPT_ECHO_OFF, &authtok, "%s", prompt);
            if (res != PAM_SUCCESS) {
                //pam_error(pamh, "Failed to get password!");
                return PAM_SYSTEM_ERR;
            }
            res = pam_set_item(pamh, PAM_AUTHTOK, authtok);
            if (res != PAM_SUCCESS) {
                //pam_error(pamh, "Failed to put password!");
                return PAM_SYSTEM_ERR;
            }
            break;
        case OP_ECHO:
            res = pam_get_item(pamh, PAM_AUTHTOK, (const void **) &authtok);
            if (res != PAM_SUCCESS) {
                //pam_info(pamh, "No password in the stack!");
                return PAM_IGNORE;
            }
            pam_info(pamh, "%s%s", prompt, authtok);
            break;
    }
    return PAM_SUCCESS;
}

// This is required sometimes to be able to log in successfully
PAM_EXTERN int pam_sm_setcred(pam_handle_t* pamh, int flags, int argc, const char** argv) {
    return PAM_IGNORE;
}
