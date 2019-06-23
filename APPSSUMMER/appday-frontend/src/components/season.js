import React, {Component} from 'react';
import { Navbar } from './Navbar';

export default class Season extends Component {
    constructor(props) {
        super(props);

        this.state = {
            seasons: [],
            matches: [],
            season: 2019,
            loaded: false,
            season_loaded: false,
            error: false
        }

        this.gotoMatch = this.gotoMatch.bind(this);
        this.fetchSeason = this.fetchSeason.bind(this);
    }

    componentDidMount() {
        fetch('http://localhost:8000/api/v1/seasons')
            .then(raw_data => raw_data.json().then(data => {
                this.setState({seasons: data, loaded: true})
            })).catch(err => {
                this.setState({error: true})
            })
        
        fetch('http://localhost:8000/api/v1/seasons/2019')
            .then(raw_data => raw_data.json().then(data => {
                this.setState({matches: data})
            })).catch(err => {
                this.setState({error: true})
            })
    }

    fetchSeason(event) {
        var i = event.target.innerText
        this.setState({season_loaded: false});
        let url = 'http://localhost:8000/api/v1/seasons/' + i
        debugger;
        fetch('http://localhost:8000/api/v1/seasons/' + i)
            .then(raw_data => raw_data.json().then(data => {
                this.setState({matches: data, season: Number(i), season_loaded: true})
            })).catch(err => {
                this.setState({error: true})
            })
        debugger;
    }

    gotoMatch(event) {
        console.log(event.target.href)
        let matchid = event.target.href
        console.log(matchid)
        let url = 'http://localhost:3000/matches/' + String(matchid);
        console.log(url);
        // window.location.href = ;
    }

    render() {
        if (this.state.loaded !== true) return <h1>Loading...</h1>
        return (
            <div>
            <Navbar/>
            <div class="jumbotron jumbotron-fluid">
                <div class="container">
                    <h1 className="display-5" style={{fontSize: '50px'}}>Seasons</h1>
                 </div>
            </div>
            <div className="col-sm-8" style={{margin: '0px auto', alignContent: 'center'}}>
                <DropDown curseason={this.state.season} seasons={this.state.seasons} onChange={this.fetchSeason}/>
                {
                    this.state.season_loaded === true  || this.state.loaded === true ?
                    <MatchesRenderer matches={this.state.matches} season={this.state.season} gotoMatch={this.gotoMatch}/>:
                    <h1>Loading...</h1>
                }
            </div>
            </div>
        );
    }

}

const DropDown = props => {
    console.log(props)
    return (
        <div>
        <div className="btn-group">
        <button style={{
            textAlign: 'center',
            margin: '20px'
        
        }}       
        type="button" className="btn btn-info dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
           {props.curseason} 
        </button>
        <div className="dropdown-menu">
            {
                props.seasons.seasons.map((val, i) => {
                    return <a className="dropdown-item" onClick={props.onChange}>{val}</a>
                })
            }
        </div>
        </div>
        {/* <select id="seasons-dropdown" onChange={props.onChange}>
            {
                props.seasons.seasons.map((val, i) => {
                    return <option key={i} value={val}>{val}</option>
                })
            }
        </select> */}
        </div>
    )
}

const MatchesRenderer = props => {
    console.log(props);
    return (
        
        <div>
            <h2>Matches in {props.season}</h2>
            <table className="table table-hover table-striped table-dark">
                <thead>
                    <tr>
                    <th>
                        #
                    </th>
                    <th>
                        Team1
                    </th>
                    <th>
                        Team2
                    </th>
                    <th>
                        Winner
                    </th>
                    <th>
                        MOM
                    </th>
                    <th>
                        Date
                    </th>
                    <th>
                        Venue
                    </th>
                    <th>
                        Links
                    </th>
                    </tr>
                </thead>
            <tbody>
            {
                props.matches.map((match, i) => {
                    return (
                        <tr>
                            <td>{i + 1}</td>
                            <td>{match.team1}</td>
                            <td>{match.team2}</td>
                            <td>{match.winner}</td>
                            <td>{match.player_of_match}</td>
                            <td>{match.date}</td>
                            <td>{match.venue}</td>
                            <td><button 
                            onClick={() => window.location.href='http://localhost:3000/matches/' + String(match.id)}
                            className="btn btn-primary"
                            >More</button></td>
                        </tr>
                    )
                })
            }
            </tbody>
            </table>
        </div>
    )
}