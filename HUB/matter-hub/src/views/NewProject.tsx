import { invoke } from "@tauri-apps/api/tauri";
import { open } from '@tauri-apps/api/dialog';
import React from 'react';
import { useNavigate } from 'react-router-dom';

export default function NewProject() {
    const [ projectName, setProjectName ] = React.useState('');
    const [ projectPath, setProjectPath ] = React.useState('');
    const navigate = useNavigate();

    return (
        <main>
            <div className="page-header">
                <h2>New Project</h2>
            </div>
            <div id="new-project">
                <div id="new-project-inputs">
                    <label>Project Name</label>
                    <input type="text" spellCheck={false} defaultValue={projectName} onChange={(e) => setProjectName(e.target.value)} />

                    <label>Project Path</label>
                    <div id="project-path">
                        <input type="text" spellCheck={false} defaultValue={projectPath} />
                        <button className="button" onClick={async () => {
                            const selected = await open({
                                multiple: false,
                                title: 'Select Project Directory',
                                directory: true,
                            });

                            if (selected && !Array.isArray(selected)) {
                                setProjectPath(selected as string);
                            }
                        }}>...</button>
                    </div>
                </div>

                <div id="new-project-buttons">
                    <button className="button secondary" onClick={() => {
                        navigate("/");
                    }}>Cancel</button>
                    <button className="button primary" onClick={() => {
                        invoke("create_project", { name: projectName, path: projectPath }).then(() => { navigate("/"); });
                    }}>Create</button>
                </div>
            </div>
        </main>
    )
}