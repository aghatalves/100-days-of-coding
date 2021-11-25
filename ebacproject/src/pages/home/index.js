import React, { useState } from 'react';
import './style.scss';
import imageDestack from '../../images/imagem-destaque.png';
import Pills from '../../components/pills';

const PLACES = [
    'Praça',
    'Parque',
    'Igreja',
    'Hotel',
    'Restaurante',
    'Zoológico',
    'Farmácia',
    'Loja',
    'Aquário'
]

const Home = () => {
    const [selectedPill, setSelectedPill] = useState('')
    return (
        <main id="main-content" className="home__container">
            <div className="home__column">
                <h1 className="home__title">São Paulo para todos</h1>
                <p className="home__text">Nossa missão é promover a socialização de pessoas que buscam por opções de entretenimento e precisam de cuidados especiais de acessibilidade, de modo a lista ambientes inclusivos.</p>
                <p className="home__text">Checamos 10 itens essenciais de acessibilidade em diversos pontos da cidade.</p>
                <div className="home__pills">
                    {
                        PLACES.map((item) => (
                            <Pills
                                local={item}
                                selected={selectedPill === item}
                                onClick={() => setSelectedPill(item)}
                            />
                        ))
                    }

                </div>
            </div>
            <div className="home__column">
                <div className="home__image home__image--destack">
                    <img src={imageDestack} alt="Imagem destaque: cadeirante" />
                </div>
            </div>
        </main>

    )
}

export default Home;