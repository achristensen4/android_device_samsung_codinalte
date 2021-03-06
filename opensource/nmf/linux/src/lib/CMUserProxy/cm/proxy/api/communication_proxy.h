/*
 * Copyright (C) ST-Ericsson SA 2010. All rights reserved.
 * This code is ST-Ericsson proprietary and confidential.
 * Any use of the code for whatever purpose is subject to
 * specific written permission of ST-Ericsson SA.
 */
 
/*!
 * \brief Stub configuration Component Manager API.
 *
 * This file contains the Component Manager API part for intializing NMF and registering Host generated stubs.
 *
 * \defgroup CM_CALLBACK_API CM Proxy CallBack API
 * \ingroup CM_PROXY_MODULE
 */

#ifndef PROXY_COMMUNICATION_H
#define PROXY_COMMUNICATION_H

#include <cm/proxy/api/private/stub-requiredapi.h>

/*****************************************************************************************/
/*  Component Manager dedicated (for host stubs registering purpose) macros definition   */
/*****************************************************************************************/

/*!
 * \brief Macro to be used used to register a set of Host stubs and skeletons
 *
 * This macro shall be called to register the generated Host stubs and skeletons.
 *
 * \note Host stubs are generated by: nmfitfc -host2mpc \<list of interface names\>.
 * Host skels are generated by: nmfitfc -mpc2host \<list of interface names\>.
 *
 * \warning By example, if the generated Host stubs and skeletons are linked into a dll, then this macro should be called when loading and initializing the given dll.
 *
 * \ingroup CM_CONFIGURATION_API
 */
#define CM_REGISTER_STUBS_SKELS(name) \
{ \
    extern t_nmf_stub_register name##_stub_register; \
    extern t_nmf_skel_register name##_skel_register; \
    CM_INTERNAL_RegisterHost2MpcInterfaces(&name##_stub_register); \
    CM_INTERNAL_RegisterMpc2HostInterfaces(&name##_skel_register); \
}

/*!
 * \brief Macro to be used used to unregister a set of Host stubs and skeletons
 *
 * This macro shall be called to unregister the generated Host stubs and skeletons for example before
 * unloading a DLL or at the end of the process.
 *
 * \note If you register N times an stubs and skeletons, you must unregister them N times too.
 * \note Don't call this macro if you have call the corresponding register macro before.
 *
 * \ingroup CM_CONFIGURATION_API
 */
#define CM_UNREGISTER_STUBS_SKELS(name) \
{ \
    extern t_nmf_stub_register name##_stub_register; \
    extern t_nmf_skel_register name##_skel_register; \
    CM_INTERNAL_UnregisterHost2MpcInterfaces(&name##_stub_register); \
    CM_INTERNAL_UnregisterMpc2HostInterfaces(&name##_skel_register); \
}

/*!
 * \brief Macro to be used used to register a set of Host stubs
 *
 * This macro shall be called to register the generated Host stubs.
 *
 * \note Host stubs are generated by: nmfitfc -host2mpc \<list of interface names\>
 *
 * \warning By example, if the generated Host stubs are linked into a dll, then this macro should be called when loading and initializing the given dll.
 *
 * \ingroup CM_CONFIGURATION_API
 */
#define CM_REGISTER_STUBS(name) \
{ \
    extern t_nmf_stub_register name##_stub_register; \
    CM_INTERNAL_RegisterHost2MpcInterfaces(&name##_stub_register); \
}

/*!
 * \brief Macro to be used used to unregister a set of Host stubs
 *
 * This macro shall be called to unregister the generated Host stubs for example before
 * unloading a DLL or at the end of the process.
 *
 * \note If you register N times a stubs, you must unregister them N times too.
 * \note Don't call this macro if you have call the corresponding register macro before.
 *
 * \ingroup CM_CONFIGURATION_API
 */
#define CM_UNREGISTER_STUBS(name) \
{ \
    extern t_nmf_stub_register name##_stub_register; \
    CM_INTERNAL_UnregisterHost2MpcInterfaces(&name##_stub_register); \
}

/*!
 * \brief Macro to be used used to register a set of Host skeletons
 *
 * This macro shall be called to register the generated Host skeletons.
 *
 * \note Host skels are generated by: nmfitfc -mpc2host \<list of interface names\>
 *
 * \warning By example, if the generated Host skels are linked into a dll, then this macro should be called when loading and initializing the given dll.
 *
 * \ingroup CM_CONFIGURATION_API
 */
#define CM_REGISTER_SKELS(name) \
{ \
    extern t_nmf_skel_register name##_skel_register; \
    CM_INTERNAL_RegisterMpc2HostInterfaces(&name##_skel_register); \
}

/*!
 * \brief Macro to be used used to unregister a set of Host skeletons
 *
 * This macro shall be called to unregister the generated Host skeletons for example before
 * unloading a DLL or at the end of the process.
 *
 * \note If you register N times a stubs, you must unregister them N times too.
 * \note Don't call this macro if you have call the corresponding register macro before.
 *
 * \ingroup CM_CONFIGURATION_API
 */
#define CM_UNREGISTER_SKELS(name) \
{ \
    extern t_nmf_skel_register name##_skel_register; \
    CM_INTERNAL_UnregisterMpc2HostInterfaces(&name##_skel_register); \
}


/*!
 * \brief Host skeletons calling facilities.
 *
 * This method allow the message retrieved through CM_GetMessage to the right skeleton.
 *
 * \param[in]   itfref          Interface reference.
 * \param[in]   message         Reference on the message to be unmarshalled.
 *
 * \ingroup CM_CALLBACK_API
 */
PUBLIC IMPORT_SHARED void CM_ExecuteMessage(
        t_nmf_interface_desc *      itfref,
        char *                      message);

/*!
 * \brief Get received message from specified callback channel.
 *
 * This method can be used to retrieve callback message from CM Engine. Returned message could then
 * be dispatch through CM_ExecuteMessage.
 *
 * \note This method must be fully synchronize with potential wrapping done in \ref CM_BindComponentToUser.
 *
 * In an environment where the client context give in \ref CM_BindComponentToUser is not wrapped,
 * message could be dispatch in the code like that:
 * \code
{
    char                        buffer[MAX_MESSAGE_SIZE];
    t_nmf_interface_desc        *itfref;
    ...
    if(CM_GetMessage(channel, &itfref, buffer, sizeof(buffer), FALSE) == CM_OK)
    {
        CM_ExecuteMessage(itfref, buffer);
    }
    ...
}
 * \endcode
 * Note that this code is able to dispatch interface reference in C or C++.
 *
 * In an environment where the client context give in \ref CM_BindComponentToUser is wrapped,
 * message could be dispatch in the code like that:
 * \code
{
    char                        buffer[MAX_MESSAGE_SIZE];
    ENSWrapperCtx               *wrapper;
    ...
    if(CM_GetMessage(channel, (void*)&wrapper, buffer, sizeof(buffer), FALSE) == CM_OK)
    {
        CM_ExecuteMessage(wrapper->WrapperItfref, buffer);
    }
    ...
}
 * \endcode
 * And where, the wrapping code of \ref CM_BindComponentToUser will look like that:
 * \code
t_cm_error ENS_Wrapper::bindComponentToUser(
        t_cm_instance_handle component,
        const char *itfname,
        t_nmf_interface_desc *itfref,
        t_uint32 fifosize)
{
    ENSWrapperCtx * wrapper = new ENSWrapperCtx();
    wrapper->WrapperItfref = itfref;

    return CM_BindComponentToUser(
                component, itfname, (void*)wrapperThis, fifosize);
}
 * \endcode
 *
 *
 * In an multi-threaded environment, message could be dispatch in the code like that:
 * \code
void MessagePuller(void)
{
    char                        buffer[MAX_MESSAGE_SIZE];
    t_nmf_interface_desc        *itfref;

    while(1) {
	    if(CM_GetMessage(channel, &itfref, buffer, sizeof(buffer), TRUE) == CM_OK) {
		    CM_ExecuteMessage(itfref, buffer);
        }
    }
}

{
    ...
    CreateThread(MessagePuller);
    ...
}
 * \endcode
 *
 * \param[in]   channel         The channel from which the message must be retrieved
 * \param[out]  clientContext   client context.
 * \param[out]  message         Reference on buffer to be unmarshalled. The buffer is allocated internally.
 * \param[in]   blockable       Indicate if the call could blocked or not.
 *
 * \exception CM_NO_MESSAGE No waited message.
 * \exception CM_BUFFER_OVERFLOW Received message is bigger that buffer give in parameter.
 *
 * \ingroup CM_CALLBACK_API
 */
PUBLIC IMPORT_SHARED t_cm_error CM_GetMessage(
        t_nmf_channel               channel,
        void                        **clientContext,
        char                        **message,
        t_bool                      blockable);

#endif /* PROXY_COMMUNICATION_H */
