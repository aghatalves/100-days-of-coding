import React from 'react';
import ReactDOM from 'react-dom';
import './styles/global.scss';
import Header from './components/header'


ReactDOM.render(
  <div className="main__wrapper">
    <div className="main__container">
      <Header />

    </div>

  </div>,
  document.getElementById('root')
);