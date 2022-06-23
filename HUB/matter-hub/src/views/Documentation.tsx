export default function Documentation() {
    return (
        <main>
            <div className="page-header">
                <h2>Documentation</h2>
                <button className="button secondary">View on GitHub<i className="mdi mdi-github" style={{ paddingLeft: 4 }} /></button>
                <button className="button primary">Open in browser<i className="mdi mdi-open-in-app" style={{ paddingLeft: 4 }} /></button>
            </div>
            <iframe src="https://jakerieger.github.io/MATTER/" title="Matter Documentation" style={{
                width: "100%",
                height: "calc(100vh - 120px)",
            }} />
        </main>
    )
}