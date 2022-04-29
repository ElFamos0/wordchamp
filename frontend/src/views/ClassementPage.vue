<template>
<div>
    <v-tabs class="justify-content-center" style="margin: auto; max-width: 240px">
        <v-tab @click="normal=true; carriere=false"> Classique </v-tab>
        <v-tab @click="normal=false; carriere=true"> Carrière </v-tab>
    </v-tabs>
    <v-table v-if="normal" theme="light" density="default" style="margin-bottom:5%; margin-left:10%; margin-right:10%; margin-top:5% ; border-radius:4px; box-shadow: rgba(0, 0, 0, 0.2) 0px 12px 28px 0px, rgba(0, 0, 0, 0.1) 0px 2px 4px 0px, rgba(255, 255, 255, 0.05) 0px 0px 0px 1px inset;">
        <template v-slot:default>
        <thead style="background:rgb(50, 50, 50); color:white">
            <tr>
                <th class="text-center" style="padding-top:10px">
                    <h3>#</h3>   
                </th>
                <th class="text-center" style="padding-top:10px">
                    <h3>Pseudo</h3>
                </th>
                <th class="text-center" style="padding-top:10px">
                    <h3>Points</h3>
                </th>
            </tr>
        </thead>
        <tbody>
            <tr v-for="userData in usersData" :key="userData.classement" :class="{'rank-first': userData.classement == 1, 'rank-second': userData.classement == 2, 'rank-third': userData.classement == 3} "> 
                <td>{{ userData.classement }}</td>
                <td>{{ userData.username }}</td>
                <td>{{ userData.points }}</td>
            </tr>
        </tbody>
        </template>
    </v-table>  
    <v-table v-if="carriere" theme="light" density="default" style="margin-bottom:5%; margin-left:10%; margin-right:10%; margin-top:5% ; border-radius:4px; box-shadow: rgba(0, 0, 0, 0.2) 0px 12px 28px 0px, rgba(0, 0, 0, 0.1) 0px 2px 4px 0px, rgba(255, 255, 255, 0.05) 0px 0px 0px 1px inset;">
        <template v-slot:default>
        <thead style="background:rgb(50, 50, 50); color:white">
            <tr>
                <th class="text-center" style="padding-top:10px">
                    <h3>#</h3>   
                </th>
                <th class="text-center" style="padding-top:10px">
                    <h3>Pseudo</h3>
                </th>
                <th class="text-center" style="padding-top:10px">
                    <h3>Elo</h3>
                </th>
            </tr>
        </thead>
        <tbody>
            <tr v-for="userData in usersData" :key="userData.classement" :class="{'rank-first': userData.classement == 1, 'rank-second': userData.classement == 2, 'rank-third': userData.classement == 3} "> 
                <td>{{ userData.classement }}</td>
                <td>{{ userData.username }}</td>
                <td>{{ userData.elo }}</td>
            </tr>
        </tbody>
        </template>
    </v-table>     
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
            normal: true,
            carriere: false,
            }
    },
    created() {
        axios.get(path).then((res)=> {
            res.data.users.forEach(element => {
                
                this.usersData.push(element);
            });
            })
    },
}
const path = `${process.env.VUE_APP_BACKEND_URL}/classement`;

</script>

<style scoped>

.rank-first {
    font-weight: bolder; 
    background:rgb(225, 209, 106);
}

.rank-second {
    font-weight: bolder;
    background:rgb(195, 195, 195);
}

.rank-third {
    font-weight: bolder; 
    background:rgb(192, 137, 80);
}
</style>