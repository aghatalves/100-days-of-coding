import React from 'react';
import ReactDOM from 'react-dom';
import './styles/global.scss';
import Header from './components/header';
import Home from './pages/home';
import CuratorItem from './components/curator';

ReactDOM.render(
  <div className="main__wrapper">
    <div className="main__container">
      <Header />
      <Home />
      {/* ESPAÇO*/}
      <CuratorItem />
    </div>

  </div>,
  document.getElementById('root')
);