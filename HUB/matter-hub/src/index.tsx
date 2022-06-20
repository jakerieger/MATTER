import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter, Routes, Route } from 'react-router-dom';

import Titlebar from './components/Titlebar';
import * as Views from './views';
import '@mdi/font/css/materialdesignicons.min.css'
import './index.css';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <React.StrictMode>
    <Titlebar />
   <BrowserRouter>
      <Routes>
        <Route path="/" element={<Views.Projects />} />
        <Route path="/new" element={<Views.NewProject />} />
      </Routes>
   </BrowserRouter>
  </React.StrictMode>
);
