/*
  This file was NOT generated from .xs source.  (The interface is not
  simple enough for that language to be useful).

  However, we do use the xsub facilities to interface with the Perl
  interpreter.
*/

#include <stdbool.h>
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>
#include <xmlrpc-c/transport.h>



static void
returnData(const char *                     const error,
           struct xmlrpc_client_transport * const transportP,
           SV *                             const execObjR,
           SV *                             const transportOpsR,
           SV *                             const errorRetR) {

    if (SvROK(errorRetR)) {
        SV * const errorRet = SvRV(errorRetR);

        if (error)
            sv_setpv(errorRet, error);
        else
            sv_setsv(errorRet, &PL_sv_undef);
    }

    if (!error) {
        SV * const execObj      = SvRV(execObjR);
        SV * const transportOps = SvRV(transportOpsR);
    
        sv_setuv(execObj, (unsigned long)transportP);
        sv_setuv(transportOps, (unsigned long)&xmlrpc_curl_transport_ops);
    }
}



static void
makeXportParms(SV *                            const xportParmsR,
               struct xmlrpc_curl_xportparms * const xportParmsP,
               unsigned int *                  const parmSizeP,
               const char **                   const errorP) {

    // TODO: extract this stuff from hash 'xportParmsR'

    xportParmsP->network_interface = NULL;
    xportParmsP->no_ssl_verifypeer = false;
    xportParmsP->no_ssl_verifyhost = false;
    xportParmsP->user_agent = NULL;
    xportParmsP->ssl_cert = NULL;
    xportParmsP->sslcerttype = NULL;
    xportParmsP->sslcertpasswd = NULL;
    xportParmsP->sslkey = NULL;
    xportParmsP->sslkeytype = NULL;
    xportParmsP->sslkeypasswd = NULL;
    xportParmsP->sslengine = NULL;
    xportParmsP->sslengine_default = false;
    xportParmsP->sslversion = XMLRPC_SSLVERSION_DEFAULT;
    xportParmsP->cainfo = NULL;
    xportParmsP->capath = NULL;
    xportParmsP->randomfile = NULL;
    xportParmsP->egdsocket = NULL;
    xportParmsP->ssl_cipher_list = NULL;

    *parmSizeP = XMLRPC_CXPSIZE(ssl_cipher_list);
    *errorP = NULL;
}



XS(XS_RPC__Xmlrpc_c__Client__Curl__transportCreate);
XS(XS_RPC__Xmlrpc_c__Client__Curl__transportCreate) {

    dXSARGS;

    if (items != 4)
        Perl_croak(aTHX_ "_transportCreate() called with %u arguments; "
                   "expected 4.", items);
    else {
        SV * const xportParmsR   = ST(0);
        SV * const execObjR      = ST(1);
        SV * const transportOpsR = ST(2);
        SV * const errorRetR     = ST(3);

        struct xmlrpc_client_transport * transportP;
        struct xmlrpc_curl_xportparms xportParms;
        const char * error;
        xmlrpc_env env;

        if (!SvROK(xportParmsR))
            error = "Tranport parameter argument is not a reference";
        else if (SvTYPE(SvRV(xportParmsR)) != SVt_PVHV)
            error = "Transport parameter argument is reference to something "
                    "other than a hash";
        else if (!SvROK(execObjR))
            error = "executable object argument is not a reference";
        else if (!SvROK(transportOpsR))
            error = "transport ops argument is not a reference";
        else
            error = NULL;

        if (!error) {
            unsigned int xportParmSize;
            makeXportParms(xportParmsR, &xportParms, &xportParmSize, &error);

            if (!error) {
                xmlrpc_env_init(&env);

                xmlrpc_curl_transport_ops.create(
                    &env, 0, "", "", (struct xmlrpc_xportparms *)&xportParms,
                    xportParmSize,
                    &transportP);

                if (env.fault_occurred)
                    error = env.fault_string;

                xmlrpc_env_clean(&env);
            }
        }
        returnData(error, transportP, execObjR, transportOpsR, errorRetR);
    }
    XSRETURN_EMPTY;
}



XS(XS_RPC__Xmlrpc_c__Client__Curl__transportDestroy);

XS(XS_RPC__Xmlrpc_c__Client__Curl__transportDestroy) {

    dXSARGS;

    if (items != 1)
        Perl_croak(aTHX_ "_transportDestroy() called with %u arguments; "
                   "expected 1.", items);
    else {
        unsigned long const _transport = SvUV(ST(0));

        struct xmlrpc_client_transport * const transportP =
            (struct xmlrpc_client_transport *)_transport;

        xmlrpc_curl_transport_ops.destroy(transportP);
    }
    XSRETURN_EMPTY;
}



XS(boot_RPC__Xmlrpc_c__Client__Curl);

XS(boot_RPC__Xmlrpc_c__Client__Curl) {

    dXSARGS;

    char * const file = __FILE__;

    XS_VERSION_BOOTCHECK;

    newXSproto("RPC::Xmlrpc_c::Client::Curl::_transportCreate",
               XS_RPC__Xmlrpc_c__Client__Curl__transportCreate, file, "$$$$");

    newXSproto("RPC::Xmlrpc_c::Client::Curl::_transportDestroy",
               XS_RPC__Xmlrpc_c__Client__Curl__transportDestroy, file, "$");

    XSRETURN_YES;
}

