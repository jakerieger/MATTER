import React from 'react';
import { appWindow } from "@tauri-apps/api/window"

export default function Titlebar() {
    return (
        <div data-tauri-drag-region className="titlebar">
            <div data-tauri-drag-region className="titlebar-left">
                <div data-tauri-drag-region>Matter Hub</div>
            </div>
            <div className="titlebar-right">
                <button className="titlebar-button" id="titlebar-minimize" onClick={() => {
                    appWindow.minimize();
                }}>
                    <i className="mdi mdi-window-minimize" />
                </button>
                <button className="titlebar-button" id="titlebar-maximize" onClick={() => {
                    appWindow.toggleMaximize();
                }}>
                    <i className="mdi mdi-window-maximize" />
                </button>
                <button className="titlebar-button" id="titlebar-close" onClick={() => {
                    appWindow.close();
                }}>
                    <i className="mdi mdi-close" />
                </button>
            </div>
        </div>
    )
}