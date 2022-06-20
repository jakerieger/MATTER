import React from "react";
import { useNavigate } from 'react-router-dom';
import { invoke } from "@tauri-apps/api/tauri";
import { IProject } from "../Interfaces";

export default function Projects() {
    const [ projects, setProjects ] = React.useState<IProject[]>([]);
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
                    {projects.map((p) => (
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
                                <button className="button"><i className="mdi mdi-dots-horizontal" /></button>
                            </td>
                        </tr>
                    ))}
                </tbody>
            </table>
        </main>
    )
}