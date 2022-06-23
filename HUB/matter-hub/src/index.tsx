import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter, Routes, Route } from 'react-router-dom';

import Titlebar from './components/Titlebar';
import * as Views from './views';
import '@mdi/font/css/materialdesignicons.min.css'
import './index.css';
import Sidebar from './components/Sidebar';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <React.StrictMode>
    <Titlebar />
    <BrowserRouter>
        <Sidebar/>
        <Routes>
          <Route path="/" element={<Views.Projects />} />
          <Route path="/new" element={<Views.NewProject />} />
          <Route path="/installs" element={<Views.Installs />} />
          <Route path="/docs" element={<Views.Documentation />} />
          <Route path="/settings" element={<Views.Settings />} />
        </Routes>
    </BrowserRouter>
  </React.StrictMode>
);
