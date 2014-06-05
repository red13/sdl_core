package com.ford.syncV4.android.service;

import com.ford.syncV4.protocol.enums.ServiceType;

/**
 * Created with Android Studio.
 * Author: Chernyshov Yuriy - Mobile Development
 * Date: 12/17/13
 * Time: 3:46 PM
 */

/**
 * This interface provide callbacks to the Service lifecycle events (Start, Stop)
 */
public interface IProxyServiceEvent {

    public void onProxyInitError(String message);

    /**
     * Dispatch when receive RPC service end message
     */
    public void onDisposeComplete();

    /**
     * Dispatch when receive disposing of the RPC service gas an error
     */
    public void onDisposeError();

    /**
     * Dispatch when receive service end message
     *
     * @param serviceType a type of the service
     */
    public void onServiceEnd(ServiceType serviceType);

    /**
     * Dispatch when receive service start message (in case of RPC Service)
     *
     * @param serviceType a type of the service
     */
    public void onServiceStart(ServiceType serviceType, String appId);

    /**
     * Dispatch when receive Ack message
     *
     * @param frameReceived frame received number
     * @param serviceType   a type of the service
     */
    public void onAckReceived(String appId, int frameReceived, ServiceType serviceType);

    /**
     * Dispatch when Service Nack received
     *
     * @param serviceType a type of the service
     */
    public void onStartServiceNackReceived(String appId, ServiceType serviceType);
}