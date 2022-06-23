import React from "react"
import { createPortal } from "react-dom";

export enum MessageBoxAction {
    OK_CANCEL,
    YES_NO,
    CONFIRM_CANCEL,
    OK
}

export enum MessageBoxType {
    INFO,
    WARNING,
    ERROR,
    QUESTION
}

export interface MessageBoxProps {
    type: MessageBoxType,
    actions: MessageBoxAction;
    title: string;
    message: string;
    open: boolean;
    setOpen: React.Dispatch<React.SetStateAction<boolean>>;
    onConfirm: () => void;
}

export default function MessageBox(props: MessageBoxProps) {
    function getIcon() : { color: string, icon: string } {
        switch (props.type) {
            case MessageBoxType.INFO:
                return { color: "var(--INFO)", icon: "mdi mdi-information" };
            case MessageBoxType.QUESTION:
                return { color: "var(--INFO)", icon: "mdi mdi-help-circle" };
            case MessageBoxType.WARNING:
                return { color: "var(--WARNING)", icon: "mdi mdi-alert" };
            case MessageBoxType.ERROR:
                return { color: "var(--DANGER)", icon: "mdi mdi-alert-octagon" };
            default:
                return { color: "var(--INFO)", icon: "mdi mdi-information" };
        }
    }

    return props.open ? (
        <>
            {createPortal(
                <div className="messagebox">
                    <div className="messagebox-box">
                        <div className="messagebox-title">
                            <i className={ getIcon().icon } style={{ color: getIcon().color }} />
                            <h2>{props.title}</h2>
                        </div>
                        <div className="messagebox-body">
                            {props.message}
                        </div>
                        <div className="messagebox-actions">
                            {props.actions === MessageBoxAction.OK_CANCEL && (
                                <div>
                                    <button className="button secondary" onClick={() => props.setOpen(false)}>Cancel</button>
                                    <button className="button primary" onClick={props.onConfirm}>Ok</button>
                                </div>
                            )}

                            {props.actions === MessageBoxAction.YES_NO && (
                                <div>
                                    <button className="button secondary" onClick={() => props.setOpen(false)}>No</button>
                                    <button className="button primary" onClick={props.onConfirm}>Yes</button>
                                </div>
                            )}

                            {props.actions === MessageBoxAction.CONFIRM_CANCEL && (
                                <div>
                                    <button className="button secondary" onClick={() => props.setOpen(false)}>Cancel</button>
                                    <button className="button primary" onClick={props.onConfirm}>Confirm</button>
                                </div>
                            )}

                            {props.actions === MessageBoxAction.OK && (
                                <div>
                                    <button className="button primary" onClick={props.onConfirm}>Ok</button>
                                </div>
                            )}
                        </div>
                    </div>
                </div>,
                document.body
            )}
        </>
    ) : null;
}