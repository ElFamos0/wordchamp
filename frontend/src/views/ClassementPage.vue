<template>
<div>
    <v-tabs class="justify-content-center" style="padding-top:1%; margin: auto; max-width: 240px">
        <v-tab @click="normal=true; carriere=false" style="font-family: 'Roboto', sans-serif;"> Classique </v-tab>
        <v-tab @click="normal=false; carriere=true" style="font-family: 'Roboto', sans-serif;"> Carrière </v-tab>
    </v-tabs>
    <v-container class="tableau mt-5" v-if="normal">
        <v-row class="haut-tableau">
            <v-col cols="4">
                <h3>#</h3>   
            </v-col>
            <v-col cols="4">
                <h3>Pseudo</h3>
            </v-col>
            <v-col cols="4">
                <h3>Points</h3>
            </v-col>
        </v-row>
        <v-row v-for="userData in usersData2" :key="userData.classement" :class="{'rank':true,'rank-first': userData.classement == 1, 'rank-second': userData.classement == 2, 'rank-third': userData.classement == 3, 'bas-tableau': userData.classement == usersData.length} "> 
            <v-col cols="4">{{ userData.classement }}</v-col>
            <v-col cols="4">{{ userData.username }}</v-col>
            <v-col cols="4">{{ userData.points }}</v-col>
        </v-row>
    </v-container>  
    <v-container class="tableau mt-5" v-if="carriere">
        <v-row class="haut-tableau">
            <v-col cols="4">
                <h3>#</h3>   
            </v-col>
            <v-col cols="4">
                <h3>Pseudo</h3>
            </v-col>
            <v-col cols="4">
                <h3>Elo</h3>
            </v-col>
        </v-row>
        <v-row v-for="userData in usersData" :key="userData.classement" :class="{'rank':true, 'rank-first': userData.classement == 1, 'rank-second': userData.classement == 2, 'rank-third': userData.classement == 3, 'bas-tableau': userData.classement == usersData.length} "> 
            <v-col cols="4">{{ userData.classement }}</v-col>
            <v-col cols="4">{{ userData.username }}</v-col>
            <v-col cols="4">{{ userData.elo }}</v-col>
        </v-row>
    </v-container>     
</div>
</template>

<script>
// import SimpleTable from 
import axios from '@/api/axios-auth'

export default {
    classement: 'ClassementPage',
    // components: SimpleTable,
    data () {
        return {
            usersData: [],
            usersData2: [],
            normal: true,
            carriere: false,
            }
    },
    created() {
        axios.get(path).then((res)=> {
            res.data.users.users.forEach(element => {
                    this.usersData.push(element);
                });
            res.data.users2.users.forEach(element => {
                    this.usersData2.push(element);
                });
            })
    },
}
const path = `${process.env.VUE_APP_BACKEND_URL}/classement`;

</script>

<style scoped>

.rank-first {
    font-weight: bolder; 
    background:rgb(225, 209, 106) !important;
}

.rank-second {
    font-weight: bolder;
    background:rgb(195, 195, 195) !important;
}

.rank-third {
    font-weight: bolder; 
    background:rgb(192, 137, 80) !important;
}

.rank {
    color: black;
    background: white;
    margin-bottom:5px;
}

.tableau {
    background:rgb(50, 50, 50);
    color:white;
    border-radius:8px;
    font-family: 'Roboto', sans-serif;
}

.haut-tableau {
    border-radius:8px;
}

.bas-tableau {
    border-radius:5px;
    margin-bottom:-5px;
}
</style>