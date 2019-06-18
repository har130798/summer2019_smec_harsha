import React, {Component} from 'react';
import { Navbar } from './Navbar';
import {FaCalendarAlt} from 'react-icons/fa';
import {GiPodiumWinner, GiTwoCoins, GiMedallist} from 'react-icons/gi';
import {MdPlace, MdInfoOutline} from 'react-icons/md';

export default class Match extends Component {
    constructor(props) {
        super(props);

        this.state = {
            match_id: props.match.params.match_id,
            cur_tab: 1,
            loaded: false,
            error: false
        }

        this.switchTab = this.switchTab.bind(this);
    }

    componentDidMount() {
        fetch('http://localhost:8000/api/v1/matches/' + String(this.state.match_id))
            .then(raw_data => raw_data.json().then(data => {
                console.log(data)
                this.setState({match: data, loaded: true})
            })).catch(err => {
                this.setState({error: true})
            })
    }

    switchTab(event) {
        // console.log(event.target.id)
        if (event.target.id === 'innings1') {
            event.target.className = 'nav-link active';
            this.setState({cur_tab: 1})
            document.getElementById('innings2').className = 'nav-link';
        } else {
            event.target.className = 'nav-link active';
            this.setState({cur_tab: -1})
            document.getElementById('innings1').className = 'nav-link';
        }
        
    }

    render() {
        if (this.state.loaded !== true) return <h1>Loading...</h1>

        return (
            <div>
            <Navbar />
            <div class="jumbotron jumbotron-fluid">
                <div class="container">
                    <h1 className="display-4" style={{fontSize: '50px'}}>{this.state.match.match_data.team1} vs {this.state.match.match_data.team2}</h1>
                 </div>
            </div>
            <div className="col-sm-8" style={{margin: '0px auto'}}>
                <h2>Match details</h2>
                <MatchData match_data={this.state.match.match_data} />
                <RenderTabs onClick={this.switchTab}/>
                {
                    this.state.cur_tab === 1 ?
                    <MatchRenderer deliveries={this.state.match.deliveries_1}/> :
                    <MatchRenderer deliveries={this.state.match.deliveries_2}/>
                }
            </div>
            </div>
        );
    }

}

const RenderTabs = props => {
    return (
        <ul className="nav nav-tabs">
            <li className="nav-item">
                <button style={{
                    outline: 'none'
                }}
                id="innings1" className="nav-link active" onClick={props.onClick}>Innings 1</button>
            </li>
            <li className="nav-item">
                <button style={{
                    outline: 'none'
                }}
                id="innings2" className="nav-link" onClick={props.onClick}>Innings 2</button>
            </li>
        </ul>
    )
}

const MatchData = props => {
    let data = props.match_data
    return (
        <div>
            <ul style={{listStyle: 'none'}}>
                <li><FaCalendarAlt style={iconCss}/>{data.date}</li>
                <li><GiMedallist style={iconCss}/> {data.player_of_match}</li>
                <li><MdPlace style={iconCss} /> {data.venue}</li>
                <li><GiPodiumWinner style={iconCss}/>{data.winner}</li>
                <li><GiTwoCoins style={iconCss}/> {data.toss_winner}</li>
                <li><MdInfoOutline style={iconCss}/> Toss decision was {data.toss_decision}</li>
                <li><MdInfoOutline style={iconCss}/>Won by {data.win_by_runs} runs</li>
                <li><MdInfoOutline style={iconCss}/>Won by {data.win_by_wickets} wickets</li>
            </ul>
        </div>
    )
}

const MatchRenderer = props => {
    return (
        <div>
            <table className="table table-striped table-dark">
                <thead>
                    <tr><th>over#</th><th>ball#</th><th>batsman</th><th>non-striker</th><th>bowler</th><th>player dismissed</th><th>dismissal kind</th><th>total runs</th></tr>
                </thead>
                <tbody>
                    {
                        props.deliveries.map((data, i) => {
                            return (
                                <tr>
                                    <td>{data.over}</td>
                                    <td>{data.ball}</td>
                                    <td>{data.batsman}</td>
                                    <td>{data.non_striker}</td>
                                    <td>{data.bowler}</td>
                                    <td>{data.player_dismissed}</td>
                                    <td>{data.dismissal_kind}</td>
                                    <td>{data.total_runs}</td>
                                </tr>
                            )
                        })
                    }
                </tbody>
            </table>
        </div>
    )
}

const iconCss = {
    'margin-right': '7px'
} 