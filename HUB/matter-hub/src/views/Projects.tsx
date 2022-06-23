import React from "react";
import { useNavigate } from 'react-router-dom';
import { invoke } from "@tauri-apps/api/tauri";
import { IProject } from "../Interfaces";
import ContextMenu from "../components/ContextMenu";
import MessageBox, { MessageBoxAction, MessageBoxType } from "../components/MessageBox";

export default function Projects() {
    const [ projects, setProjects ]                 = React.useState<IProject[]>([]);
    const [ menuRootNode, setMenuRootNode ]         = React.useState('body');
    const [ contextMenuOpen, setContextMenuOpen ]   = React.useState(false);
    const [ deleteMsgBoxOpen, setDeleteMsgBoxOpen ] = React.useState(false);
    const [ activeProject, setActiveProject ]       = React.useState(0);
    const navigate = useNavigate();
    
    React.useEffect(() => {
        invoke("get_projects").then((p) => {
            setProjects(p as IProject[]);
        });
    }, []);

    return (
        <main>
            <div className="page-header">
                <h2>Projects</h2>
                <button className="button secondary">Add Existing...</button>
                <button className="button primary" onClick={() => {
                    navigate("/new");
                }}>New Project</button>
            </div>

            <input type="text" placeholder="Search" id="project-search" />

            <table>
                <thead>
                    <tr>
                        <th><i className="mdi mdi-star-outline" /></th>
                        <th>Name</th>
                        <th>Last Modified</th>
                        <th>Engine Version</th>
                        <th></th>
                    </tr>
                </thead>
                <tbody>
                    {projects.map((p, idx) => (
                        <tr key={p.path}>
                            <td>
                                <i className={p.favorite ? "mdi mdi-star" : "mdi mdi-star-outline"} />
                            </td>
                            <td>
                                <div>{p.name}</div>
                                <div id="path">{p.path}</div>
                            </td>
                            <td>{new Date(p.last_modified * 1000).toLocaleDateString()}</td>
                            <td>{p.engine_version}</td>
                            <td>
                                <button className="button" id={"menu_" + idx.toString()} onClick={() => {
                                    const rootNode = "#menu_" + idx.toString();
                                    setActiveProject(idx);
                                    setMenuRootNode(rootNode);
                                    setContextMenuOpen(true);
                                }}><i className="mdi mdi-dots-horizontal" /></button>
                            </td>
                        </tr>
                    ))}
                </tbody>
            </table>
            <ContextMenu
                open={contextMenuOpen}
                setOpen={setContextMenuOpen}
                rootNode={menuRootNode}
            >
                <div className="context-menu-item"><i className="mdi mdi-folder"/> Show in Explorer</div>
                <div className="context-menu-item"><i className="mdi mdi-cube"/> Change engine version...</div>
                <div className="context-menu-item"><i className="mdi mdi-close"/> Remove from list</div>
                <div className="context-menu-seperator"/>
                <div
                    className="context-menu-item"
                    style={{ color: 'var(--DANGER)' }}
                    onClick={() => setDeleteMsgBoxOpen(true)}
                >
                    <i className="mdi mdi-delete"/> Delete
                </div>
            </ContextMenu>
            <MessageBox
                type={MessageBoxType.WARNING}
                actions={MessageBoxAction.YES_NO}
                title="Delete Project?"
                message="Are you sure you want to delete this project? This cannot be undone."
                open={deleteMsgBoxOpen}
                setOpen={setDeleteMsgBoxOpen}
                onConfirm={() => {
                    invoke("delete_project", { id: activeProject }).then(() => {
                        const new_projects: IProject[] = [];
                        for (let i = 0; i < projects.length; i++) {
                            if (i !== activeProject)
                                new_projects.push(projects[i]);
                            else
                                continue;
                        }
                        setProjects([...new_projects]);
                        setDeleteMsgBoxOpen(false);
                    });
                }}
            />
        </main>
    )
}