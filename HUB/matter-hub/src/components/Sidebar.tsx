import React from "react"
import { useNavigate, useLocation } from 'react-router-dom';

enum Views {
    Projects,
    Installs,
    Documentation,
    Settings,
};

export default function Sidebar() {
    const [ currentView, setCurrentView ] = React.useState<Views>(Views.Projects);
    const location = useLocation();

    React.useEffect(() => {
        if (location.pathname.startsWith("/projects")) {
            setCurrentView(Views.Projects);
        }
        else if (location.pathname.startsWith("/installs")) {
            setCurrentView(Views.Installs);
        }
        else if (location.pathname.startsWith("/docs")) {
            setCurrentView(Views.Documentation);
        }
        else if (location.pathname.startsWith("/settings")) {
            setCurrentView(Views.Settings);
        }
    }, [ location ]);

    return (
        <div className="sidebar">
            <img src={ require('../assets/logo.png') } id="logo" />
            <div id="sidebar-nav">
                <a
                    href="/"
                    className={ currentView === Views.Projects ? "active" : undefined }
                >
                    <i className="mdi mdi-cube"/> Projects
                </a>
                <a
                    href="/installs"
                    className={ currentView === Views.Installs ? "active" : undefined }
                >
                    <i className="mdi mdi-download"/> Installs
                </a>
                <a
                    href="/docs"
                    className={ currentView === Views.Documentation ? "active" : undefined }
                >
                    <i className="mdi mdi-book"/> Documentation
                </a>
                <a
                    href="/settings"
                    className={ currentView === Views.Settings ? "active" : undefined }
                >
                    <i className="mdi mdi-cog"/> Settings
                </a>
            </div>

            <div id="sidebar-footer">
                <div>v1.0.0rc1</div>
                <div>
                    <a href="https://github.com/jakerieger/MATTER"><i className="mdi mdi-github" /></a>
                </div>
            </div>
        </div>
    )
}