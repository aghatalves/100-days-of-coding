import React from 'react';
import './style.scss';
import curatorPhoto from '../../images/foto.jpeg';

function CuratorItem() {

    return (
        <div className="curator__container">
            <div className="curator__photo">
                <img src={curatorPhoto} alt="Foto do curador Ághata Alves" />
            </div>
            <div className="curator__details">
                <div>
                    <h3>Ághata Alves</h3>
                    <h6>Curadoria</h6>
                </div>
                <p>Aluna de Ciência da Computação, iniciando carreira em desenvolvimento Backend.
                    Minhas principais linguagens de estudo e desenvolvimento são o PHP e Node.Js.</p>
            </div>
        </div>
    )

}

export default CuratorItem;